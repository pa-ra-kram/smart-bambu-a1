#include "Display.h"

Display::Display(uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t rst)
    : tft(cs, dc, sda, scl, rst), rstPin(rst) {
}

void Display::begin() {
    // Manual reset sequence
    pinMode(rstPin, OUTPUT);
    digitalWrite(rstPin, HIGH);
    delay(100);
    digitalWrite(rstPin, LOW);
    delay(100);
    digitalWrite(rstPin, HIGH);
    delay(100);
    
    // Initialize display
    tft.initR(INITR_144GREENTAB);
    tft.setRotation(0);
    tft.fillScreen(ST77XX_BLACK);
    
    drawStaticElements();
}

void Display::drawStaticElements() {
    // Title
    tft.setTextColor(ST77XX_CYAN);
    tft.setTextSize(1);
    tft.setCursor(10, 10);
    tft.println("Bambu A1 Monitor");
    tft.drawLine(10, 22, 120, 22, ST77XX_WHITE); // horizontal line under title

    // Static labels
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(10, 32);
    tft.print("Temp:");
    tft.setCursor(10, 50);
    tft.print("Flame:");
    tft.setCursor(10, 68);
    tft.print("Fan Level:");
    tft.setCursor(10, 86);
    tft.print("Speed:");

    // Initialize values (blank)
    tft.setCursor(70, 32);
    tft.print("        ");
    tft.setCursor(70, 50);
    tft.print("        ");
    tft.setCursor(70, 68);
    tft.print("   ");
    tft.setCursor(70, 86);
    tft.print("    ");
}

void Display::update(float temp, bool flame, int fanLevel) {
    updateTemperature(temp);
    updateFlameStatus(flame);
    updateFanLevel(fanLevel);
    updateSpeedPercent((fanLevel * 100) / 3);
}

void Display::updateTemperature(float temp) {
    // Clear the area with a filled rectangle
    tft.fillRect(70, 32, 58, 8, ST77XX_BLACK);
    tft.setCursor(70, 32);
    tft.setTextColor(ST77XX_WHITE);
    tft.printf("%5.1f C", temp);
    lastTemp = temp;
}

void Display::updateFlameStatus(bool flame) {
    // Clear the area with a filled rectangle
    tft.fillRect(70, 50, 58, 8, ST77XX_BLACK);
    tft.setCursor(70, 50);
    tft.setTextColor(flame ? ST77XX_RED : ST77XX_GREEN);
    tft.print(flame ? "DETECTED" : "OK");
    lastFlame = flame;
}

void Display::updateFanLevel(int level) {
    // Clear the area with a filled rectangle
    tft.fillRect(70, 68, 58, 8, ST77XX_BLACK);
    tft.setCursor(70, 68);
    tft.setTextColor(ST77XX_WHITE);
    tft.printf("%d", level);
    lastFanLevel = level;
}

void Display::updateSpeedPercent(int percent) {
    // Clear the area with a filled rectangle
    tft.fillRect(70, 86, 58, 8, ST77XX_BLACK);
    tft.setCursor(70, 86);
    tft.printf("%d%%", percent);
    lastSpeedPercent = percent;
} 