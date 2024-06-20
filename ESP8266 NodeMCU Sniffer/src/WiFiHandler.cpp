#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "WiFiHandler.h"
#include "UtilityFunctions.h"

WiFiHandler::WiFiHandler(Adafruit_ST7735& tft) : m_tft(tft)
{
    m_ssid = "Your ESP Friend";
    m_psk = "admin1234";
}

//Configures the softAP
void WiFiHandler::setupAP() 
{

// Set ESP8266 to AP mode with specified SSID and password
    Serial.println("\nSetting up ESP8266 Access Point!...");
    Serial.print("\nSSID: ");
    Serial.println(m_ssid);
    Serial.print("Password: ");
    Serial.println(m_psk);

    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "Setting up Access Point!...");

    WiFi.persistent(false);

// Set up the access point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(m_ssid, m_psk);

//Device's IP address to connect to web server
    Serial.print("Device's IP Address: ");
    Serial.println(WiFi.softAPIP());

    Serial.println("\nAccess Point Configured!");
    

// Register the callback for the AP station connection event
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(std::bind(&WiFiHandler::onStationConnected, this, std::placeholders::_1));
    stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(std::bind(&WiFiHandler::onStationDisconnected, this, std::placeholders::_1));
}


//Converts mac address to a string, so that it becomes printable
String WiFiHandler::macToString(const uint8_t* mac) 
{
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

void WiFiHandler::removeDevice(String macAddress) 
{
    int indexToRemove = -1;
    // Find the index of the device to remove
    for (int i = 0; i < m_deviceCount; ++i)
    {
        if (m_connectedDevices[i] == macAddress) {
            indexToRemove = i;
            break;
        }
    }
    // If the device is found, remove it by shifting elements
    if (indexToRemove != -1) 
    {
        for (int i = indexToRemove; i < m_deviceCount - 1; ++i) 
        {
            m_connectedDevices[i] = m_connectedDevices[i + 1];
        }
    m_deviceCount--;
    }
}

// Callback function for when a client connects to the AP
void WiFiHandler::onStationConnected(const WiFiEventSoftAPModeStationConnected& event) 
{
    Serial.print("\nNew device connected, MAC address: ");
    Serial.println(macToString(event.mac));

    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "New device connected: " + macToString(event.mac));
 
//Store the mac address in an array
    m_connectedDevices[m_deviceCount] = (macToString(event.mac));
    m_deviceCount += 1;

    Serial.print("Total devices now: ");
    Serial.println(m_deviceCount);
}

//Callback function when a client disconnects from the AP
void WiFiHandler::onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& event) 
{
    String macAddress = macToString(event.mac);
    Serial.print("\nDevice disconnected: ");
    Serial.println(macAddress);
    removeDevice(macAddress);
    Serial.print("Total devices now: ");
    Serial.println(m_deviceCount);

    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "Device Disconnected: " + macToString(event.mac));
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

//Scans all networks nearby
String WiFiHandler::scanNetworks() 
{
    Serial.println("\nScanning Networks!...");
    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "Scanning Networks!...");


    int n = WiFi.scanNetworks();
    String json = "[";
    for (int i = 0; i < n; ++i) {
        if (i) json += ",";
        json += "{";
        json += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
        json += "\"rssi\":" + String(WiFi.RSSI(i));
        json += "}";
    }
    json += "]";
    Serial.println("\nScan Complete!");
    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "\nScan Complete!");
    return json;
}

//Connects to a WiFi network using given ssid and password
bool WiFiHandler::connectToNetwork(const char* ssid, const char* password) 
{
    WiFi.begin(ssid, password);
    Serial.println("\nAttempting To Connect To " + WiFi.SSID());
    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "\nSuccessfully Connected To: " + WiFi.SSID() + "\nRSSI: " + String(WiFi.RSSI()));
    
    while (WiFi.status() != WL_CONNECTED && m_retries < 20)
    {
        delay(500);
        m_retries++;
    }

    Serial.println("\nSuccessfully Connected To: " + WiFi.SSID() + "\nRSSI: " + String(WiFi.RSSI()));
    UtilityClass::clearDisplay(m_tft);
    UtilityClass::printToDisplay(m_tft, "\nSuccessfully Connected To: " + WiFi.SSID() + "\nRSSI: " + String(WiFi.RSSI()));
    
    return (WiFi.status() == WL_CONNECTED);
}

//Returns a bool of if the device is connected to a WiFi network
bool WiFiHandler::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

//Returns the SSID of the current network that the network is connected to
String WiFiHandler::getConnectedSSID()
{
    if (isConnected()) 
    {
        return WiFi.SSID();
    }
    else
    {
        return "Not Connected to a Network";
    }
}

//Disconnects from the current network connection
void WiFiHandler::disconnect() 
{
    if(isConnected())
    {
        Serial.println("Disconnecting from Network: " + WiFi.SSID());
        UtilityClass::clearDisplay(m_tft);
        UtilityClass::printToDisplay(m_tft, "Disconnecting from Network: " + WiFi.SSID());

        WiFi.disconnect();
    }
}


