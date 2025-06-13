#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Display class for Bambu A1 Monitor
// Now uses improved alignment and formatting for readability
class Display {
public:
    Display(uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t rst);
    void begin();
    void update(float temp, bool flame, int fanLevel);
    
private:
    Adafruit_ST7735 tft;
    uint8_t rstPin;  // Store reset pin number
    float lastTemp = -999;
    bool lastFlame = false;
    int lastFanLevel = -1;
    int lastSpeedPercent = -1;
    
    void drawStaticElements();
    void updateTemperature(float temp);
    void updateFlameStatus(bool flame);
    void updateFanLevel(int level);
    void updateSpeedPercent(int percent);
}; 