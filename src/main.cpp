#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define ONE_WIRE_BUS 15  // GPIO pin for DS18B20 data
#define FLAME_DO_PIN 14  // GPIO pin for flame sensor digital output
#define FAN_PWM_PIN 17   // GPIO pin for fan MOSFET (PWM)
#define LED_R_PIN 2      // RGB LED Red pin (D2 - available on FireBeetle ESP32-E)
#define LED_G_PIN 4      // RGB LED Green pin (D4 - available on FireBeetle ESP32-E)
#define LED_B_PIN 13     // RGB LED Blue pin (D13 - available on FireBeetle ESP32-E)
#define BUZZER_PIN 33    // Buzzer pin (moved from 22/SCL)

// TFT Display pins (using proper SPI pins)
#define TFT_CS   5       // Chip Select
#define TFT_DC   16      // Data/Command
#define TFT_RST  25      // Reset
#define TFT_MOSI 23      // SPI MOSI (correct pin)
#define TFT_SCLK 18      // SPI SCLK (correct pin)

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const int pwmChannel = 0;
const int pwmFreq = 25000; // 25kHz for quiet fan operation
const int pwmResolution = 8; // 8 bits: 0-255

int lastFanLevel = -1;
unsigned long lastTestBeep = 0;

void setup() {
    Serial.begin(115200);
    sensors.begin();
    pinMode(FLAME_DO_PIN, INPUT);
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Set up PWM for fan
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(FAN_PWM_PIN, pwmChannel);
    
    // Initialize TFT display
    tft.initR(INITR_144GREENTAB); // 1.44" display
    tft.setRotation(0);
    tft.fillScreen(ST77XX_BLACK);
    
    // Display "Hello" message
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(20, 20);
    tft.println("Hello!");
    tft.setTextSize(1);
    tft.setCursor(10, 50);
    tft.println("Bambu A1 Monitor");
    
    // Test beep on startup
    Serial.println("Testing buzzer on startup...");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    
    delay(2000); // Show hello message for 2 seconds
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

void beep(int count, int duration) {
    for (int i = 0; i < count; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(duration);
        digitalWrite(BUZZER_PIN, LOW);
        delay(duration);
    }
}

void setFanFeedback(int fanLevel) {
    // Set color based on fan level
    switch (fanLevel) {
        case 0: setRGB(0, 0, 255); break;      // Blue
        case 1: setRGB(0, 255, 0); break;      // Green
        case 2: setRGB(255, 255, 0); break;    // Yellow
        case 3: setRGB(255, 0, 0); break;      // Red
    }
    
    // Beep when fan level changes
    if (fanLevel != lastFanLevel) {
        beep(fanLevel + 1, 100); // 1 beep for level 0, 2 for level 1, etc.
        lastFanLevel = fanLevel;
    }
}

void updateDisplay(float temp, bool flame, int fanLevel) {
    tft.fillScreen(ST77XX_BLACK);
    
    // Title
    tft.setTextColor(ST77XX_CYAN);
    tft.setTextSize(1);
    tft.setCursor(10, 10);
    tft.println("Bambu A1 Monitor");
    
    // Temperature
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(10, 30);
    tft.print("Temp: ");
    tft.print(temp, 1);
    tft.println(" C");
    
    // Flame status
    tft.setCursor(10, 50);
    tft.print("Flame: ");
    tft.setTextColor(flame ? ST77XX_RED : ST77XX_GREEN);
    tft.println(flame ? "DETECTED" : "OK");
    
    // Fan level
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(10, 70);
    tft.print("Fan: Level ");
    tft.println(fanLevel);
    
    // Fan speed percentage
    tft.setCursor(10, 90);
    int speedPercent = (fanLevel * 100) / 3;
    tft.print("Speed: ");
    tft.print(speedPercent);
    tft.println("%");
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
    updateDisplay(tempC, flameDetected, fanLevel);

    // Test beep every 10 seconds for debugging
    if (millis() - lastTestBeep > 10000) {
        Serial.println("Test beep...");
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        lastTestBeep = millis();
    }

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" °C | Flame: ");
    Serial.print(flameDetected ? "DETECTED" : "NOT DETECTED");
    Serial.print(" | Fan Level: ");
    Serial.println(fanLevel);

    delay(2000);
} 