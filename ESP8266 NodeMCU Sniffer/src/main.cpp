#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>


//WiFi Credentials
const char* ssid = "test1234"; //WiFi SSID
const char* password = "admin"; //WiFi Password

//Led Pin Number
const int ledPin = D4; 

//WiFi and Server Handler Objects
WiFiHandler wifiHandler(ssid, password);
ServerHandler serverHandler; 


// Initialize serial communication
void setup() 
{
  pinMode(ledPin, OUTPUT); //Sets LED light to output only
  Serial.begin(9600); //Baud rate set to 9600 for serial communication

  delay(2000); //Wait before setup before setting up WiFi

  wifiHandler.connect(); //Setup WiFi
  serverHandler.begin(); //Setup server
  
  Serial.println("\nHello, ESP8266!");
}

void loop() 
{
// Handle server clients
  serverHandler.handleClient();
  wifiHandler.printConnectedDevices();
}