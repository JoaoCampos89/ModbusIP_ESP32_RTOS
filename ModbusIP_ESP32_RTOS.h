/*
    ModbusIP_ESP32.h - Header for Modbus IP ESP32 Library
	Adapted entirely from ModbusIP_ESP8266.h from André Sarmento Barbosa


*/
#include <Modbus_ESP32.h>
#include <WiFi.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/event_groups.h"

#include "tcpip_adapter.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/api.h"
#include "lwip/tcp.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/priv/api_msg.h"
#include "lwip/err.h"




#ifndef MODBUSIP_ESP32_RTOS_H
#define MODBUSIP_ESP32_RTOS_H

#define MODBUSIP_PORT 	  502
#define MODBUSIP_MAXFRAME 200
#define MODBUSIP_TIMEOUT   10
#ifndef MODBUSIP_SSID
#define MODBUSIP_SSID   "your_ssid"
#endif
#ifndef MODBUSIP_PASS
#define MODBUSIP_PASS   "your_pass"
#endif

class ModbusIP_ESP32_RTOS : public Modbus_ESP32 {
    private:
        
    public:
        byte MBAP[7];
        ModbusIP_ESP32_RTOS();
        void config(const char* ssid, const char* password);
      //  void task();
};




#endif //MODBUSIP_ESP32_H
