#include <iostream>

#include <EEPROM.h>
#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>
#include <LittleFS.h>

//Led Pin Number
const int ledPin = D4; 

//WiFi and Server Handler Objects
WiFiHandler wifiHandler;
ServerHandler serverHandler; 

/*|----------------------------------------------------------------|*/

// Initialize serial communication
void setup() 
{
  pinMode(ledPin, OUTPUT); //Sets LED light to output only
  Serial.begin(9600); //Baud rate set to 9600 for serial communication

  LittleFS.begin(); //Initialize the LittleFS file system
  serverHandler.begin(); //Setup web server
  wifiHandler.connect(); //Setup WiFi
    
  Serial.println("\nHello, ESP8266!");
}

void loop() 
{
// Server Handler
  serverHandler.handleClient();
}