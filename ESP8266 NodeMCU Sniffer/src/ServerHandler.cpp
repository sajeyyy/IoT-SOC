#include "ServerHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

ServerHandler::ServerHandler() {
  // Setup your routes and handlers here
  m_Server.on("/", HTTP_GET, std::bind(&ServerHandler::handleRoot, this));
}

void ServerHandler::begin() {
  // Start the server
  m_Server.begin();
  Serial.println("HTTP server started");
}

void ServerHandler::handleClient() {
  // Handle incoming client requests
  m_Server.handleClient();
}

void ServerHandler::handleRoot() {
  // Handle the root URL
  m_Server.send(200, "text/plain", "Hello, ESP8266!");
}