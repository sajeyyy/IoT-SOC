#ifndef UTILITY_CLASS_H
#define UTILITY_CLASS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class UtilityClass {
public:
    static void printToDisplay(Adafruit_ST7735 &tft, const String &message);
    static void clearDisplay(Adafruit_ST7735 &tft);
};

#endif