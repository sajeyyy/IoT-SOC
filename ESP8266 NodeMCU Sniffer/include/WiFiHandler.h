#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <ESP8266WiFi.h>

class WiFiHandler
{
    public:
        WiFiHandler();
        void connect();
        WiFiEventHandler stationConnectedHandler;
        WiFiEventHandler stationDisconnectedHandler;

        void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt);
        void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) ;

        int getDeviceCount();
        String getConnectedDevice(int index);

        String scanNetworks();
        bool connectToNetwork(const char* ssid, const char* psk);
        bool isConnected();
        String getConnectedSSID(); // Public method to get the connected SSID
        void disconnect(); // Public method to disconnect from the network

    private:
        const char* m_ssid;
        const char* m_psk;
        int m_retries;

        bool m_newUser;
        int m_deviceCount;
        String m_connectedDevices[6];

        void removeDevice(String macAddress);
        String macToString(const uint8_t* mac);
};

#endif