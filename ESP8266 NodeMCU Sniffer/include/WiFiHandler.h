#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <ESP8266WiFi.h>

class WiFiHandler
{
    public:
        WiFiHandler();
        void connect();

        String macToString(const uint8_t* mac);
        WiFiEventHandler stationConnectedHandler;
        void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt);

        int getDeviceCount();
        String getConnectedDevice(int index);

    private:
        const char* m_ssid;
        const char* m_psk;
        
        bool m_newUser;
        int m_deviceCount;
        String m_connectedDevices[6];
};

#endif