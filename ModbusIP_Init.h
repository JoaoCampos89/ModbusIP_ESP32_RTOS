#include <ModbusIP_ESP32_RTOS.h>
//http://lwip.wikia.com/wiki/Netconn_bind
ModbusIP_ESP32_RTOS mb;
static void modbus_server(void *);

static void socket_modbus_server(void *pvParameters)
{
    struct netconn *conn, *newconn;
    err_t err;
    conn = netconn_new(NETCONN_TCP);
    netconn_bind(conn, NULL, MODBUSIP_PORT );
    netconn_listen(conn);
    do
    {
      // http://www.nongnu.org/lwip/2_0_x/api_8h.html#a28430d1d86733f1bf98dc31305c42104
      // Use get address to filter the ip
        err = netconn_accept(conn, &newconn);
        uint32_t tasks = uxTaskGetNumberOfTasks();
        if (err == ERR_OK)
        {
            // printf("new conn+task :: %d :: %d :: %d\n", tasks, esp_get_free_heap_size());
            xTaskCreatePinnedToCore(modbus_server, "modbus_server", 4096,  newconn, 20, NULL, 0);
        }
    }
    while (err == ERR_OK);
    /* Delete Listening Server */
    netconn_close(conn);
    netconn_delete(conn);
}




static void modbus_server(void *pvParameters)
{

		struct netconn *conn = (struct netconn *)pvParameters;
    struct netbuf *inbuf;
    char *buffer;
	//	uint8_t buffer[128] = {0};
    uint16_t len;
    bool close_flag = true;
    char url[256] = { 0 };
    char * is_event_stream = NULL;
    err_t err;

		err = netconn_recv(conn, &inbuf);
		if (err == ERR_OK)
		{
					netbuf_data(inbuf, (void**)&buffer, &len);
					int i = 0;
					while (i < 7) {
							mb.MBAP[i] = buffer[i];
							i++;
					}

					mb._len = mb.MBAP[4] << 8 | mb.MBAP[5];
					mb._len--; // Do not count with last byte from MBAP
					if (mb.MBAP[2] !=0 || mb.MBAP[3] !=0) return;   //Not a ModbusIP_ESP32_RTOS packet
					if (mb._len > MODBUSIP_MAXFRAME) return;      //Length is over ModbusIP_ESP32_MAXFRAME

					mb._frame = (byte*) malloc(mb._len);
					i = 0;
					while (i < mb._len){
							mb._frame[i] = buffer[7+i];  //Forget MBAP and take just modbus pdu
							i++;
					}

					mb.receivePDU(mb._frame);

					if (mb._reply != MB_REPLY_OFF) {
							//MBAP
							mb.MBAP[4] = mb._len >> 8;
							mb.MBAP[5] = mb._len | 0x00FF;
							buffer[4] = mb.MBAP[4];
							buffer[5] = mb.MBAP[5];

							i = 0;
							while (i < mb._len){
									buffer[i+7] = mb._frame[i];
									i++;
							}
							netconn_write(conn, buffer, mb._len + 7, NETCONN_NOCOPY);
					free(mb._frame);
					mb._len = 0;

					}
		}
		netbuf_delete(inbuf);
		if (close_flag)
			 {
					 netconn_close(conn);
					 if(err == ERR_OK)
					 {
						 netconn_free(conn);
					 }
					 else
					 {
							 printf("DID NOT FREE NETCONN BECAUSE err != ERR_OK => %d\n", err);
					 }
			 }
		vTaskDelete(NULL);
	}




void mb_config_init(const char* ssid, const char* password){
  mb.config(ssid, password);
  xTaskCreatePinnedToCore(&socket_modbus_server, "socket_modbus_server", 4096, NULL, 1, NULL, 0);
}
