#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>


//WiFi Credentials
const char* ssid = "test1234";
const char* password = "admin";

//Led Pin Number
const int ledPin = D4;

//WiFi and Server Handler Objects
WiFiHandler wifiHandler(ssid, password);
ServerHandler serverHandler;

void flashLED(int pin, int onDuration, int offDuration) 
{
  digitalWrite(pin, HIGH);
  delay(onDuration);
  digitalWrite(pin, LOW);
  delay(offDuration);
}

// Initialize serial communication
void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(2000);

  wifiHandler.connect();

  serverHandler.begin();
  
  Serial.println("\nHello, ESP8266!");

  // Flash LED to show device is connected and running
  for (int i = 3; i < 6; ++i) 
  {
    flashLED(ledPin, i * 100, 100);
  }
}

void loop() 
{
// Handle server clients
  serverHandler.handleClient();
}
