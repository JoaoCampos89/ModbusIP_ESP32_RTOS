/*
    ModbusIP_ESP32.h - Header for Modbus IP ESP32 Library
	Adapted entirely from ModbusIP_ESP8266.h from André Sarmento Barbosa

*/
#include "ModbusIP_ESP32_RTOS.h"

//WiFiServer server(MODBUSIP_PORT);

ModbusIP_ESP32_RTOS::ModbusIP_ESP32_RTOS() {

}



void ModbusIP_ESP32_RTOS::config(const char* ssid, const char* password) {
	WiFi.begin(ssid, password);

//	server.begin();
}
