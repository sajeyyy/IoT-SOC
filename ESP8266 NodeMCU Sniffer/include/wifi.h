#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

class WiFiHandler {
public:
  WiFiHandler(const char* ssid, const char* password);
  void connect();
  // Add more functions as needed

private:
  const char* ssid;
  const char* password;
};

#endif