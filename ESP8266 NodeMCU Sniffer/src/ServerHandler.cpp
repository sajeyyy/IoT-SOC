#include "ServerHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

ServerHandler::ServerHandler() 
{
// Setup routes and handlers
  m_Server.on("/", HTTP_GET, std::bind(&ServerHandler::handleRoot, this));
}

void ServerHandler::begin() 
{
// Start the server
  m_Server.begin();
  Serial.println("\nHTTP server started!");
}

void ServerHandler::handleClient() 
{
// Handle incoming client requests
  m_Server.handleClient();
}

void ServerHandler::handleRoot() 
{
// Open the HTML file from littleFS file system
  File htmlFile = LittleFS.open("/index.html", "r");

// Check if the file opened successfully
  if (htmlFile) 
  {
    Serial.println("File opened successfully!");
// Send the contents of the file as the HTTP response
    m_Server.streamFile(htmlFile, "text/html");
    htmlFile.close();
  } 
  else 
  {
    Serial.println("Failed to open file!");
    // If the file failed to open, send an error response
    m_Server.send(500, "text/plain", "Internal Server Error");
  }
}
