#include <Arduino.h>

void setup() {
  // Initialization code, runs once
  Serial.begin(115200);  // Initialize serial communication
  delay(1000);           // Wait for serial to initialize
  Serial.println("Hello, ESP8266!");
}

void loop() {
  // Main code, runs repeatedly
  Serial.println("Looping...");
  delay(1000);
}
