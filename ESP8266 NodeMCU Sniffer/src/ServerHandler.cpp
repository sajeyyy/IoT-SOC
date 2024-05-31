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
	m_Server.on("/images", HTTP_GET, std::bind(&ServerHandler::handleImages, this)); 
  	m_Server.on("/devices", HTTP_GET, std::bind(&ServerHandler::handleDeviceList, this)); 

	// Catch-all handler for any other GET requests
    m_Server.onNotFound([this]() 
	{
        handleFile(m_Server.uri());
    });
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
    File cssFile = LittleFS.open("/style.css", "r");
    
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

void ServerHandler::handleImages() 
{
	Dir dir = LittleFS.openDir("/images");
	String html = "<html><body><h1>Image List</h1><ul>";
	
	while (dir.next()) {
		String fileName = dir.fileName();
		String filePath = "/images/" + fileName;
		// Generate an HTML link for each file
		html += "<li><a href=\"" + filePath + "\">" + fileName + "</a></li>";
	}
	html += "</ul></body></html>";
	m_Server.send(200, "text/html", html);
}

void ServerHandler::handleFile(String path) {
    String contentType = getContentType(path); 
    File file = LittleFS.open(path, "r");

    if (!file) {
        Serial.println("File not found: " + path);
        m_Server.send(404, "text/plain", "404: File Not Found");
        return;
    }

    Serial.println("File sent: " + path);
    m_Server.streamFile(file, contentType);
    file.close();
}

// This function determines the content type based on the file extension
String ServerHandler::getContentType(String filename) {
    if (filename.endsWith(".htm")) return "text/html";
    else if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".jpg")) return "image/jpeg";
    
	(Serial.println("\nIncompatible File Type!")); 
	return "text/plain";
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

void ServerHandler::on(const char* uri, HTTPMethod method, std::function<void()> handler) {
    m_Server.on(uri, method, handler);
}

void ServerHandler::send(int code, const char* content_type, const String& content) {
    m_Server.send(code, content_type, content);
}

bool ServerHandler::hasArg(const char* name) {
    return m_Server.hasArg(name);
}

String ServerHandler::arg(const char* name) {
    return m_Server.arg(name);
}



