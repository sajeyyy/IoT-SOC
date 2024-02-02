#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <ESP8266WebServer.h>

class ServerHandler
{
public:
    ServerHandler(char* networkName, char* pass);
    void begin();
    void handleClient();

private:
    ESP8266WebServer m_Server;
    void handleRoot();
    const char* SSID;
    const char* password;
};

#endif
