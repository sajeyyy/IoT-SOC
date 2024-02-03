#include "ServerHandler.h"
#include "WiFiHandler.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>


//WiFi Credentials
const char* ssid = "test";
const char* password = "test1234";

//Led Pin Number
const int ledPin = D4;

//WiFi and Server Handler Objects
WiFiHandler wifiHandler(ssid, password);

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
  Serial.println("\n\nHello, ESP8266!");

  wifiHandler.connect();

  // Flash LED to show device is connected and running
  for (int i = 3; i < 6; ++i) 
  {
    flashLED(ledPin, i * 100, i * 100);
  }
}

void loop() 
{
  
}
