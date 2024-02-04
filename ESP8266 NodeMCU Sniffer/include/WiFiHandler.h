#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <ESP8266WiFi.h>

class WiFiHandler
{
    public:
        WiFiHandler(const char* ssid, const char* password);
        void connect();
        void printConnectedDevices();
  
    private:
        const char* m_ssid;
        const char* m_password;

        IPAddress m_connectedDevices[4];
        int m_deviceCount;
};

#endif