#include <OneWire.h>
#include <DallasTemperature.h>
#include "Display.h"

#define ONE_WIRE_BUS 15  // GPIO pin for DS18B20 data
#define FLAME_DO_PIN 14  // GPIO pin for flame sensor digital output
#define FAN_PWM_PIN 17   // GPIO pin for fan MOSFET (PWM)
#define LED_R_PIN 2      // RGB LED Red pin (D2 - available on FireBeetle ESP32-E)
#define LED_G_PIN 4      // RGB LED Green pin (D4 - available on FireBeetle ESP32-E)
#define LED_B_PIN 13     // RGB LED Blue pin (D13 - available on FireBeetle ESP32-E)

// TFT Display pins
#define TFT_CS   12      // Chip Select
#define TFT_DC   16      // Data/Command
#define TFT_RST  25      // Reset
#define TFT_SDA  23      // SDA/Data pin
#define TFT_SCL  18      // SCL/Clock pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Display display(TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RST);

const int pwmChannel = 0;
const int pwmFreq = 25000; // 25kHz for quiet fan operation
const int pwmResolution = 8; // 8 bits: 0-255

int lastFanLevel = -1;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting Bambu A1 Monitor...");
    
    sensors.begin();
    pinMode(FLAME_DO_PIN, INPUT);
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);

    // Set up PWM for fan
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(FAN_PWM_PIN, pwmChannel);
    
    // Initialize display
    display.begin();
    
    Serial.println("Setup complete!");
}

void setFanSpeed(int level) {
    // Map level to PWM duty cycle
    int duty = 0;
    switch (level) {
        case 0: duty = 0; break;        // Off
        case 1: duty = 64; break;       // Low (~25%)
        case 2: duty = 128; break;      // Medium (~50%)
        case 3: duty = 255; break;      // High (100%)
    }
    ledcWrite(pwmChannel, duty);
}

void setRGB(int r, int g, int b) {
    analogWrite(LED_R_PIN, r);
    analogWrite(LED_G_PIN, g);
    analogWrite(LED_B_PIN, b);
}

void setFanFeedback(int fanLevel) {
    // Set color based on fan level
    switch (fanLevel) {
        case 0: setRGB(0, 0, 255); break;      // Blue
        case 1: setRGB(0, 255, 0); break;      // Green
        case 2: setRGB(255, 255, 0); break;    // Yellow
        case 3: setRGB(255, 0, 0); break;      // Red
    }
    
    // Update last fan level
    lastFanLevel = fanLevel;
}

void loop() {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    int flameDigital = digitalRead(FLAME_DO_PIN);
    bool flameDetected = (flameDigital == LOW);

    // Fan speed logic based on temperature
    int fanLevel = 0;
    if (tempC < 35) {
        fanLevel = 0; // Off
    } else if (tempC < 45) {
        fanLevel = 1; // Low
    } else if (tempC < 55) {
        fanLevel = 2; // Medium
    } else {
        fanLevel = 3; // High
    }
    
    setFanSpeed(fanLevel);
    setFanFeedback(fanLevel);
    display.update(tempC, flameDetected, fanLevel);

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" °C | Flame: ");
    Serial.print(flameDetected ? "DETECTED" : "NOT DETECTED");
    Serial.print(" | Fan Level: ");
    Serial.println(fanLevel);

    delay(2000);
} 