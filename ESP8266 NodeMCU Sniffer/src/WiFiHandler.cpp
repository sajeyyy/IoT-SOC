#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

WiFiHandler::WiFiHandler(const char* ssid, const char* password) 
    : m_ssid(ssid), m_password(password) {
}

void WiFiHandler::connect() {
// Set ESP8266 to AP mode with specified SSID and password
  Serial.println("\n\nSetting up ESP8266 Access Point...");
  Serial.print("\nSSID: ");
  Serial.println(m_ssid);
  Serial.print("Password: ");
  Serial.println(m_password);

  WiFi.softAP(m_ssid, m_password);

  Serial.println("\nESP8266 Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}
