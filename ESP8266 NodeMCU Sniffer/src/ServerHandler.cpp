#include "ServerHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

ServerHandler::ServerHandler()
{
// Setup routes and handlers
  m_Server.on("/", HTTP_GET, std::bind(&ServerHandler::handleRoot, this));
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




