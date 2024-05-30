#include <iostream>
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
ServerHandler serverHandler(wifiHandler); 

/*|----------------------------------------------------------------|*/


String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

void listDir(const String& directoryName) {
    Dir dir = LittleFS.openDir(directoryName);

    while (dir.next()) {
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();

        Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());

        if (dir.isDirectory()) {
            listDir(directoryName + fileName + "/");
        }
    }
}

// Initialize the filesystem, server, and wifi
void setup() 
{
	pinMode(ledPin, OUTPUT); 
	Serial.begin(9600); //Baud rate set to 9600 for serial communication

	//Initialize the LittleFS file system
	if(LittleFS.begin())
	{
		Serial.println("\nFile System Initialized!");
		listDir("/");
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