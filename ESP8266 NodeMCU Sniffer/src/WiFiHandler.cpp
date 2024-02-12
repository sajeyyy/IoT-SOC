#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

WiFiHandler::WiFiHandler()
{
    ssid = "ConnectToMePlz";
    psk = "admin1234";
}

void WiFiHandler::connect() 
{
// Set ESP8266 to AP mode with specified SSID and password
    Serial.println("\n\nSetting up ESP8266 Access Point...");
    Serial.print("\nSSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(psk);

// WiFi Configuration will not be saved in flash memory 
    WiFi.persistent(false);

// Set up an access point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);

//Device's IP address to connect to web server
    Serial.print("Device's IP Address: ");
    Serial.println(WiFi.softAPIP());

// Register the callback for the station connection event
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(std::bind(&WiFiHandler::onStationConnected, this, std::placeholders::_1));
}

//Converts mac address to string, so it's printable
String WiFiHandler::macToString(const uint8_t* mac) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

// Callback function for when a client connects
void WiFiHandler::onStationConnected(const WiFiEventSoftAPModeStationConnected& event) 
{
    Serial.print("\nNew device connected, MAC address: ");
    Serial.println(macToString(event.mac));

//Stores mac address in an array
    m_connectedDevices[m_deviceCount++] = (macToString(event.mac));
}
