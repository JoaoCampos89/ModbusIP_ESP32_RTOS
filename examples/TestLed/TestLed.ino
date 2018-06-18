/*
  Modbus-Arduino Example - Test Led (Modbus IP ESP32)
  Control a Led on GPIO0 pin using Write Single Coil Modbus Function
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/

#include "ModbusIP_Init.h"

//Modbus Registers Offsets (0-9999)
const int LED_COIL = 100;
//Used Pins
const int ledPin = 0; //GPIO0


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

  pinMode(ledPin, OUTPUT);
  mb.addCoil(LED_COIL);
}

void loop() {

   //Attach ledPin to LED_COIL register
   digitalWrite(ledPin, mb.Coil(LED_COIL));
}
