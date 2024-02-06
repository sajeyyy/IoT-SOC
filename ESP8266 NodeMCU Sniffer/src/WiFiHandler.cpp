#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

WiFiHandler::WiFiHandler(const char* ssid, const char* password) 
{
    m_ssid = ssid;
    m_password = password;
    m_newUser = false;
}

void WiFiHandler::connect() 
{
// Set ESP8266 to AP mode with specified SSID and password
  Serial.println("\n\nSetting up ESP8266 Access Point...");
  Serial.print("\nSSID: ");
  Serial.println(m_ssid);
  Serial.print("Password: ");
  Serial.println(m_password);

  WiFi.softAP(m_ssid, m_password);

// Register the callback for station connection event
    using namespace std::placeholders;
    WiFi.onSoftAPModeStationConnected(std::bind(&WiFiHandler::onStationConnected, this, _1));

  Serial.println("\nESP8266 Access Point Started!");
  Serial.print("Device's IP Address: ");
  Serial.println(WiFi.softAPIP());
}

String WiFiHandler::macToString(const uint8_t* mac) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

// Callback function for when a client connects
void WiFiHandler::onStationConnected(const WiFiEventSoftAPModeStationConnected& event) 
{
    Serial.println("onStationConnected callback triggered");
    Serial.print("New device connected, MAC address: ");
    Serial.println(macToString(event.mac));
  
    m_connectedDevices[m_deviceCount++] = (macToString(event.mac));
    
    // Set the flag to indicate a new device
    m_newUser = true;
}

void WiFiHandler::printConnectedDevices() 
{
  if(m_newUser)
  {
    Serial.println("\nConnected Devices:\n");
    for (int i = 0; i < m_deviceCount; ++i)
    {
        Serial.print("Device ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(m_connectedDevices[i]);
    }
    m_newUser = false;
  }
}
