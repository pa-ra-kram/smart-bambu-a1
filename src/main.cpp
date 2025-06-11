#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 15  // GPIO pin for DS18B20 data
#define FLAME_DO_PIN 14  // GPIO pin for flame sensor digital output

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(115200);
    sensors.begin();
    pinMode(FLAME_DO_PIN, INPUT);
}

void loop() {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    int flameDigital = digitalRead(FLAME_DO_PIN);

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" °C | Flame: ");
    Serial.println(flameDigital == LOW ? "DETECTED" : "NOT DETECTED");

    delay(2000);
}