#include "UtilityFunctions.h"

void UtilityClass::printToDisplay(Adafruit_ST7735 &tft, const String &message) {
    tft.println(message);
}

void UtilityClass::clearDisplay(Adafruit_ST7735 &tft) {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
}