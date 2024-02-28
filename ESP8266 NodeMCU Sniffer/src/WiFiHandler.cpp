#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>


WiFiHandler::WiFiHandler()
{
    m_ssid = "Your ESP Friend";
    m_psk = "admin1234";
}


//Configures the softAP
void WiFiHandler::connect() 
{
// Set ESP8266 to AP mode with specified SSID and password
    Serial.println("\nSetting up ESP8266 Access Point...");
    Serial.print("\nSSID: ");
    Serial.println(m_ssid);
    Serial.print("Password: ");
    Serial.println(m_psk);

// WiFi Configuration will not be saved in flash memory 
    WiFi.persistent(false);

// Set up an access point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(m_ssid, m_psk);

//Device's IP address to connect to web server
    Serial.print("Device's IP Address: ");
    Serial.println(WiFi.softAPIP());

    Serial.println("\nAccess Point Configured!");

// Register the callback for the AP station connection event
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(std::bind(&WiFiHandler::onStationConnected, this, std::placeholders::_1));
}


//Converts mac address to string, so that it becomes printable
String WiFiHandler::macToString(const uint8_t* mac) 
{
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}


// Callback function for when a client connects to the AP
void WiFiHandler::onStationConnected(const WiFiEventSoftAPModeStationConnected& event) 
{
    Serial.print("\nNew device connected, MAC address: ");
    Serial.println(macToString(event.mac));

//Stores mac address in an array
    m_connectedDevices[m_deviceCount] = (macToString(event.mac));
    m_deviceCount += 1;

    Serial.print("Total devices now: ");
    Serial.println(m_deviceCount);
}


//Returns the number of connected devices
int WiFiHandler::getDeviceCount()
{
    return m_deviceCount;
}


//Iterates through the connected devices and returns the MAC address of each device 
String WiFiHandler::getConnectedDevice(int index) 
{
    if (index >= 0 && index < m_deviceCount) 
    {
        return m_connectedDevices[index];
    }
    else 
    {
        Serial.println("Index out of bounds");
        return "";
    }
}

