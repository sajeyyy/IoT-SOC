#include <iostream>
#include "ServerHandler.h"
#include "WiFiHandler.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Preferences.h>
#include <LittleFS.h>

//Led Pin Number
const int ledPin = D4; 

//WiFi and Server Handler Objects
WiFiHandler wifiHandler;
ServerHandler serverHandler(wifiHandler); 

/*|----------------------------------------------------------------|*/

// Initialize the filesystem, server, and wifi
void setup() 
{
	pinMode(ledPin, OUTPUT); //Sets LED light to output only
	Serial.begin(9600); //Baud rate set to 9600 for serial communication

	//Initialize the LittleFS file system
	if(LittleFS.begin())
	{
		Serial.println("\nFile System Initialized!");
	}
	else
	{
		Serial.println("\nFile System Failed to Mount!");
	}

	serverHandler.begin(); // Begin the server
	delay(2000);
	wifiHandler.connect(); //Setup WiFi

	Serial.println("\nWelcome ESP8266!");
}


void loop() 
{
  serverHandler.handleClient();
}