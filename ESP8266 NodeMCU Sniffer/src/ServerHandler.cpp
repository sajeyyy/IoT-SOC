#include "ServerHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

ServerHandler::ServerHandler(WiFiHandler& wifiHandler) : m_Server(80), m_WiFiHandler(wifiHandler)
{
// Setup routes and handlers
	m_Server.on("/", HTTP_GET, std::bind(&ServerHandler::handleRoot, this));
  	m_Server.on("/style.css", HTTP_GET, std::bind(&ServerHandler::handleCSS, this));
  	m_Server.on("/script.js", HTTP_GET, std::bind(&ServerHandler::handleJS, this));
  	m_Server.on("/devices", HTTP_GET, std::bind(&ServerHandler::handleDeviceList, this)); // Register endpoint
}

// Start the server
void ServerHandler::begin()
{
  	m_Server.begin();
  	Serial.println("\nHTTP server started!");
}

//Method to handle client requests
void ServerHandler::handleClient()
{
  	m_Server.handleClient();
}

void ServerHandler::handleRoot() 
{
// Open HTML file
  	File htmlFile = LittleFS.open("/index.html", "r");

	// Send HTML file if successfully opened
	if (htmlFile) 
	{
		m_Server.streamFile(htmlFile, "text/html");
		htmlFile.close();
		Serial.println("\nHTML file sent to the server successfully!");
	} 
	else 
	{
		Serial.println("\nHTML file not found!");
		m_Server.send(500, "text/plain", "Internal Server Error - HTML file");
	}
}

void ServerHandler::handleJS() 
{
    File jsFile = LittleFS.open("/scripts.js", "r");
    if (jsFile) 
    {
    	m_Server.streamFile(jsFile, "application/javascript");
      	jsFile.close();
      	Serial.println("JavaScript file sent to the server successfully!");
    } 
    else 
    {
      	m_Server.send(404, "text/plain", "404: Not Found");
    }
}

void ServerHandler::handleCSS() 
{
    File cssFile = LittleFS.open("/styles.css", "r");
    
    if (cssFile) 
    {
      	m_Server.streamFile(cssFile, "text/css");
      	cssFile.close();
      	Serial.println("CSS file sent to the server successfully!");
    }

    else 
    {
      	m_Server.send(404, "text/plain", "404: Not Found");
    }
}

void ServerHandler::handleDeviceList() 
{
    String json = "[";
    int deviceCount = m_WiFiHandler.getDeviceCount();
    
    for (int i = 0; i < deviceCount; ++i) 
    {
      	if (i > 0) 
      	{
        	json += ", ";
      	}

      	String deviceMAC = m_WiFiHandler.getConnectedDevice(i);
      	json += "\"" + deviceMAC + "\"";
    }
	json += "]";
   	 m_Server.send(200, "application/json", json);
}



