#include "ServerHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>

ServerHandler::ServerHandler(char* networkName, char* pass) 
{
    SSID = networkName;
    password = pass;
}

void ServerHandler::begin() {
    m_Server.on("/", HTTP_GET, std::bind(&ServerHandler::handleRoot, this));
    m_Server.begin();
    Serial.println("HTTP server started");
}

void ServerHandler::handleRoot() {
    m_Server.send(200, "text/html", "<html><body><h1>Hello from ESP8266!</h1></body></html>");
}

void ServerHandler::handleClient() {
    m_Server.handleClient();
}
