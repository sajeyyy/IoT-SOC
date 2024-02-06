#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <ESP8266WiFi.h>

class WiFiHandler
{
    public:
        WiFiHandler(const char* ssid, const char* password);
        void connect();
        void printConnectedDevices();
        void onStationConnected(const WiFiEventSoftAPModeStationConnected& event);
        String macToString(const uint8_t* mac);

    private:
        const char* m_ssid;
        const char* m_password;
        
        bool m_newUser;
        int m_deviceCount;
        String m_connectedDevices[4];
};

#endif