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
    void on(const char* uri, HTTPMethod method, std::function<void()> handler);
    void send(int code, const char* content_type, const String& content);
    bool hasArg(const char* name);
    String arg(const char* name);

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
