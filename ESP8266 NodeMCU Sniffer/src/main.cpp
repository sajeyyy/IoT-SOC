#include <iostream>

#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>

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

  delay(2000); //Wait before setup before setting up WiFi and Server

  serverHandler.begin(); //Setup server
  delay(500); //Give enough time between setups
  wifiHandler.connect(); //Setup WiFi
    
  Serial.println("\nHello, ESP8266!");
}

void loop() 
{
// Handle server clients
  serverHandler.handleClient();

  delay(250);
}