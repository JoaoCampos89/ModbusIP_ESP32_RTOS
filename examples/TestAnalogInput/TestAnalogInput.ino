/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP32)
  Read Analog sensor on Pin ADC (ADC input between 0 ... 1V)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/

#include "ModbusIP_Init.h"

//Modbus Registers Offsets (0-9999)
const int SENSOR_IREG = 100;


long ts;

void setup() {
    Serial.begin(115200);

    mb_config_init("myssid", "mypass");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Add SENSOR_IREG register - Use addIreg() for analog Inputs
    mb.addIreg(SENSOR_IREG);

    ts = millis();
}

void loop() {

   //Read each two seconds
   if (millis() > ts + 2000) {
       ts = millis();
       //Setting raw value (0-1024)
       mb.Ireg(SENSOR_IREG, analogRead(A0));
   }
}
