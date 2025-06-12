#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 15  // GPIO pin for DS18B20 data
#define FLAME_DO_PIN 14  // GPIO pin for flame sensor digital output
#define FAN_PWM_PIN 17   // GPIO pin for fan MOSFET (PWM)
#define LED_R_PIN 18     // RGB LED Red pin
#define LED_G_PIN 19     // RGB LED Green pin
#define LED_B_PIN 21     // RGB LED Blue pin
#define BUZZER_PIN 22    // Buzzer pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

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
    
    // Test beep on startup
    Serial.println("Testing buzzer on startup...");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
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

void loop() {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    int flameDigital = digitalRead(FLAME_DO_PIN);

    // Fan speed logic based on temperature
    int fanLevel = 0;
    if (tempC < 30) {
        fanLevel = 0; // Off
    } else if (tempC < 40) {
        fanLevel = 1; // Low
    } else if (tempC < 50) {
        fanLevel = 2; // Medium
    } else {
        fanLevel = 3; // High
    }
    
    setFanSpeed(fanLevel);
    setFanFeedback(fanLevel);

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
    Serial.print(flameDigital == LOW ? "DETECTED" : "NOT DETECTED");
    Serial.print(" | Fan Level: ");
    Serial.println(fanLevel);

    delay(2000);
} 