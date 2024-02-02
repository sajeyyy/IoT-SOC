#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>


//Declare Variables
const char* ssid = "test";
const char* password = "test1234";

// Initialize serial communication
void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Hello, ESP8266!");
}

void loop() 
{
  Serial.println("Looping...");
  delay(1000);
}