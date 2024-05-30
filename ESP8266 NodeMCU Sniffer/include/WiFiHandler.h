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

    private:
        const char* m_ssid;
        const char* m_psk;
        
        bool m_newUser;
        int m_deviceCount;
        String m_connectedDevices[6];

        void removeDevice(String macAddress);
        String macToString(const uint8_t* mac);
};

#endif