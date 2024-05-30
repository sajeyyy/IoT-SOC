#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <ESP8266WebServer.h>
#include "WiFiHandler.h"

class ServerHandler
{
public:
    ServerHandler(WiFiHandler& WiFiHandler);
    void begin();
    void handleClient();

private:
    ESP8266WebServer m_Server;
    WiFiHandler& m_WiFiHandler;
    void handleRoot();
    void handleJS();
    void handleCSS();
    void handleImages();
    void handleDeviceList();

    void handleFile(String path);
    String getContentType(String filename);
};

#endif
