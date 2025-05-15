#include <iostream>
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include "ServerHandler.h"
#include "WiFiHandler.h"
#include "UtilityFunctions.h"

// Pin Definitions
#define LED_PIN       D4  // LED PIN

// WiFi and Server Handler Objects
WiFiHandler wifiHandler;
ServerHandler serverHandler(wifiHandler);


/*|----------------------------------------------------------------|*/


String formatBytes(size_t bytes) 
{
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

void listDir(const String& directoryName) 
{
  Dir dir = LittleFS.openDir(directoryName);

  while (dir.next()) 
  {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();

    Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());

    if (dir.isDirectory()) {
        listDir(directoryName + fileName + "/");
    }
  }
}

// Initialize the filesystem, server, and WiFi
void setup() 
{
	pinMode(LED_PIN, OUTPUT); 
	Serial.begin(9600); //Baud rate set to 9600 for serial communication
  Serial.println("\n\nStarting ESP8266..."); 


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

// Handle scan requests
  serverHandler.on("/scan", HTTP_GET, []() 
  {
    String json = wifiHandler.scanNetworks();
    serverHandler.send(200, "application/json", json);
  });

// Handle connect requests
  serverHandler.on("/connect", HTTP_POST, []() {
    if (serverHandler.hasArg("plain")) {
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, serverHandler.arg("plain"));
      String ssid = doc["ssid"];
      String password = doc["password"];

      bool success = wifiHandler.connectToNetwork(ssid.c_str(), password.c_str());

      if (success) 
      {
        serverHandler.send(200, "text/plain", "Connected to " + ssid);
      } 
      else 
      {
        serverHandler.send(500, "text/plain", "Failed to connect to " + ssid);
      }
    }
    else 
    {
      serverHandler.send(400, "text/plain", "Bad Request");
    }
  });


  // Handle status requests
  serverHandler.on("/status", HTTP_GET, []() {
  if (wifiHandler.isConnected()) 
  {
    serverHandler.send(200, "text/plain", "Connected to " + wifiHandler.getConnectedSSID());
  } 
  else 
  {
    serverHandler.send(200, "text/plain", "Not connected");
  }});


  // Handles disconnect requests
  serverHandler.on("/disconnect", HTTP_GET, []() {
      wifiHandler.disconnect();
      serverHandler.send(200, "text/plain", "Disconnected");
  });

	serverHandler.begin(); // Begin the server
	delay(3000);
	wifiHandler.setupAP(); //Setup softAP

	Serial.println("\nWelcome ESP8266!");
}


void loop() 
{
  serverHandler.handleClient();
}