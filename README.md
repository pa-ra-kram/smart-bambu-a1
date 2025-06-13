# Bambu Lab A1 Enclosure Smart Monitor

A smart, WiFi-enabled monitoring and control system for your Bambu Lab A1 3D printer enclosure. This project aims to improve safety, convenience, and insight for your 3D printing setup by tracking temperature, detecting hazards, and automating cooling—all viewable from a simple web dashboard.

> **Note:** Development is currently on a FireBeetle ESP32-E board for ease of prototyping. The code and wiring are designed to be easily portable to a smaller ESP32 board with camera (e.g., ESP32-CAM) for final deployment.

---

## 🚀 Project Overview

This project uses a FireBeetle ESP32-E board as the main controller to monitor and control the environment inside your 3D printer enclosure. The system is designed to:

- **Monitor temperature** inside the enclosure.
- **Detect fire and electrical current** for safety and diagnostics.
- **Automatically control cooling fans** to protect electronics.
- **Display real-time data** on a local TFT display and future web dashboard.
- **Log events and errors** for easy troubleshooting.
- **Support wireless firmware updates** and future sensor expansion.

---

## 🛠️ Hardware Setup (Current Stage)

Current working setup:

- **FireBeetle ESP32-E** board placed on a breadboard for prototyping.
- **Power rails:**  
  - Left rail: 5V (from BEC, for ESP32 and sensors)  
  - Right rail: 24V (from printer AMS port, for fans)
- **Common ground**: All GNDs tied together.

> **Note:** The FireBeetle ESP32-E is used for development. For final deployment, the project can be ported to a compact ESP32 board with camera support.

**Current Status:**  
Core functionality complete - temperature monitoring, flame detection, fan control, RGB feedback, and TFT display all working.

---

## 🧰 Components Used

- **FireBeetle ESP32-E** – Main controller (WiFi, Bluetooth, USB programming)
- **DS18B20 Temperature Sensor** – Digital temperature monitoring
- **3-pin Flame Sensor** – Fire safety detection
- **SCT-013-000 Current Sensor** – Power monitoring (planned)
- **ST7735 128x128 RGB TFT** – Local status display
- **4-pin RGB LED** – Visual feedback
- **24V Fans** – Active cooling with PWM control
- **5V BEC** – Power regulation from 24V AMS port

---

## 🖥️ Features (Current Status)

- ✅ Real-time temperature monitoring (DS18B20)
- ✅ Automatic fan control based on temperature (4 levels)
- ✅ Fire detection with flame sensor
- ✅ RGB LED visual feedback (color-coded fan levels)
- ✅ TFT display showing live sensor data
- 🔄 Power usage monitoring (SCT-013-000 planned)
- 🔄 Web dashboard for live data and logs
- 🔄 Wireless firmware updates (OTA)

---

## 📦 Getting Started

1. **Breadboard your FireBeetle ESP32-E** and connect 5V/24V rails as described above.
2. **Connect to your computer** via USB for programming.
3. **Upload the provided firmware** using PlatformIO or Arduino IDE.
4. **Wire sensors and display** according to the pin assignments below.

---

## 📚 FireBeetle ESP32-E Board Specs

- Dual-core 32-bit Xtensa LX6 CPU (up to 240MHz)
- 520KB SRAM, 4MB Flash
- WiFi 802.11 b/g/n, Bluetooth 4.2 LE
- USB-C connector for programming and power
- 3.3V and 5V power outputs
- Deep sleep: <10µA, Active: ~80mA
- Operating voltage: 3.3V-5.5V

---

## 🧩 Pinout Reference

For wiring and hardware reference, see the official FireBeetle ESP32-E pinout:

![FireBeetle ESP32-E Pinout](https://dfimg.dfrobot.com/enshop/image/data/DFR0654/pinout.png)

**Reference:** [DFRobot FireBeetle ESP32-E Official Documentation](https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654#6.%20Pinout)

---

## 🧪 Sensors & Modules Used

### 1. Vibration Sensor (SW-420)
- **Description:** Detects vibration or movement, triggers digital output when vibration exceeds threshold.
- **Specs:**
  - Operating Voltage: 3.3V–5V
  - Digital output (HIGH/LOW)
  - Adjustable sensitivity
- **Reference:** [Robu.in - SW-420 Vibration Sensor](https://robu.in/product/vibration-sensor-module-alarm-motion-sensor-module-vibration-switch-sw-420/)

### 2. Temperature Sensor (DS18B20)
- **Description:** Digital temperature sensor using 1-Wire protocol, supports multiple sensors on one pin.
- **Specs:**
  - Temperature Range: -55°C to +125°C
  - Accuracy: ±0.5°C
  - Operating Voltage: 3.0V–5.5V
  - 1-Wire digital interface
- **Reference:** [REES52 - DS18B20 Digital Temperature Sensor](https://rees52.com/products/ds18b20-digital-temperature-sensor-module-for-arduino-ab032)

### 3. Flame Sensor
- **Description:** Detects flame or light in the 760–1100nm wavelength range, outputs analog and digital signals.
- **Specs:**
  - Operating Voltage: 3.3V–5V
  - Analog and digital outputs
  - Detection angle: ~60°
- **Reference:** [Quartz Components - Flame Sensor](https://quartzcomponents.com/products/flame-fire-sensor-module)

### 4. TFT Display (ST7735, 1.44" 128x128)
- **Description:** SPI-based color TFT display for local status and graphics.
- **Specs:**
  - Resolution: 128x128 pixels
  - Controller: ST7735
  - Interface: SPI (SCK, MOSI, CS, DC, RESET)
  - Operating Voltage: 3.3V–5V
- **Reference:** [Robu.in - 1.44" 128x128 TFT ST7735](https://robu.in/product/1-44-inch-128x128-st7735-controller-spi-serial-port-tft-display/)

### 5. Current Sensor (SCT-013-000)
- **Description:** Non-invasive AC current sensor (clamp type), outputs analog signal proportional to current.
- **Specs:**
  - Measurement Range: 0–100A AC
  - Output: 0–1V (with burden resistor)
  - Non-invasive, split-core
- **Reference:** [Robu.in - SCT-013-000 Current Sensor](https://robu.in/product/sct-013-000-100a-non-invasive-ac-current-sensor-split-core-type-clamp-sensor/)

---

## 🧮 Current Wiring Summary

All components are successfully connected and tested on the FireBeetle ESP32-E:

### **Active Connections**
| Device | GPIO Pin | Connection Type | Status |
|--------|----------|----------------|--------|
| DS18B20 Temperature | GPIO 15 | 1-Wire Digital | ✅ Working |
| Flame Sensor | GPIO 14 | Digital Input | ✅ Working |
| Fan Control | GPIO 17 | PWM Output | ✅ Working |
| RGB LED (R,G,B) | GPIO 2,4,13 | PWM Output | ✅ Working |
| TFT Display | GPIO 12,16,18,23,25 | SPI Interface | ✅ Fixed (SDA/SCL) |

### **Planned Connections**
| Device | GPIO Pin | Connection Type | Status |
|--------|----------|----------------|--------|
| Current Sensor | GPIO 36 | Analog Input | 🔄 Planned |

**Note:** All pin assignments verified against official FireBeetle ESP32-E pinout documentation.

---

## 📝 Project Status & Roadmap

### ✅ **Completed Features**
- [x] FireBeetle ESP32-E board breadboarded and powered
- [x] DS18B20 temperature sensor connected and readings verified
- [x] Flame sensor (3-pin digital) connected and working (range ~15cm)
- [x] 24V fan control with PWM based on temperature (4 speed levels)
- [x] RGB LED visual feedback for fan levels (color-coded)
- [x] TFT display integration with live sensor data
- [x] Fan control logic implemented and tested

### 🔄 **In Progress / Planned**
- [ ] Add SCT-013-000 current sensor for print state detection
- [ ] Develop web dashboard for remote monitoring
- [ ] Add OTA (Over-The-Air) firmware updates
- [ ] Implement data logging and historical charts
- [ ] Add WiFi configuration portal
- [ ] Create enclosure mounting system

---

## 🌀 24V Fan Control Integration (Complete)

- **Type:** PWM-controlled 24V fans via N-channel MOSFET
- **Wiring:**
  - Fan + → 24V rail
  - Fan - → MOSFET drain
  - MOSFET source → GND rail
  - MOSFET gate → GPIO 17 (ESP32-E)
  - Flyback diode across fan terminals for protection
- **Control Logic:**
  - Level 0 (Off): <35°C
  - Level 1 (Low, 25%): 35-44°C
  - Level 2 (Medium, 50%): 45-54°C
  - Level 3 (High, 100%): ≥55°C
- **Testing:** Successfully tested with heat gun; fan speed responds correctly to temperature changes.

---

## 🌈 RGB LED Visual Feedback (Complete)

- **Type:** 4-pin RGB LED (common cathode)
- **Wiring:**
  - R, G, B → GPIO 2, 4, 13 (FireBeetle ESP32-E) with 220Ω resistors
  - Common cathode → GND rail
- **Color Coding:**
  - Blue: Fan off (<35°C)
  - Green: Low speed (35-44°C)
  - Yellow: Medium speed (45-54°C)
  - Red: High speed (≥55°C)
- **Note:** Buzzer integration skipped for now; may be added later for audio feedback.

---

## 📺 TFT Display Integration (Complete)

- **Goal:** Add a 1.44" 128x128 ST7735 TFT display to show real-time sensor data and system status.
- **Display Content:**
  - Temperature reading (xx.x °C format)
  - Fan level (0-3) and speed percentage (0-100%)
  - Flame sensor status (OK/DETECTED with color coding)
  - System title and status
- **Wiring:**
  - VCC → 3.3V rail
  - GND → GND rail
  - SCL → GPIO 18 (Clock line)
  - SDA → GPIO 23 (Data line)
  - CS → GPIO 12 (Chip Select)
  - DC → GPIO 16 (Data/Command, sometimes labeled A0)
  - RESET → GPIO 25 (Reset, sometimes labeled RST)
- **Implementation Details:**
  - Uses Adafruit ST7735 and GFX libraries
  - Robust text clearing with fillRect() to prevent artifacts
  - Color-coded status indicators (white for normal, red/green for alerts)
  - Optimized refresh rate (2-second intervals)
  - Static elements drawn once at startup
  - Dynamic updates for sensor values
- **Testing:** Successfully displays all sensor data with clean updates and no artifacts.

---

## 🔥 Flame Sensor (3-pin Digital) Integration

- **Type:** 3-pin digital flame sensor module
- **Wiring:**
  - VCC → 3.3V rail
  - GND → GND rail
  - DO (Digital Out) → GPIO 14 (ESP32-E)
- **Code:** Reads digital output; prints "DETECTED" when flame is present (LOW), "NOT DETECTED" otherwise.
- **Range:** ~15cm (may vary by module and environment)
- **Note:** For greater coverage or directionality, consider upgrading to a 5-channel flame sensor module in the future (with 5 LEDs in a round shape).

---

## 🧩 FireBeetle ESP32-E Complete Pinout Reference

**⚠️ CRITICAL: Use this table as the definitive reference for ALL pin assignments!**

Based on [official DFRobot documentation](https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654#6.%20Pinout)

### **Power Pins**
| Physical Pin | Function | Voltage | Max Current | Notes |
|--------------|----------|---------|-------------|-------|
| 3V3 | 3.3V Output | 3.3V | 600mA | For sensors/modules |
| 5V | 5V Input | 5V | - | Main power input |
| GND | Ground | 0V | - | Multiple GND pins |
| VIN | Voltage Input | 7-12V | - | Alternative power |

### **Available GPIO Pins on FireBeetle ESP32-E**
| GPIO | Pin Label | Type | PWM | ADC | Current Usage | Available |
|------|-----------|------|-----|-----|---------------|-----------|
| 2 | D2 | Digital I/O | ✅ | ✅ | **RGB Red** | ❌ |
| 4 | D4 | Digital I/O | ✅ | ✅ | **RGB Green** | ❌ |
| 12 | D12 | Digital I/O | ✅ | ✅ | **TFT CS** | ❌ |
| 13 | D13 | Digital I/O | ✅ | ✅ | **RGB Blue** | ❌ |
| 14 | D14 | Digital I/O | ✅ | ✅ | **Flame Sensor** | ❌ |
| 15 | D15 | Digital I/O | ✅ | ✅ | **DS18B20** | ❌ |
| 16 | D16 | Digital I/O | ✅ | ❌ | **TFT DC** | ❌ |
| 17 | D17 | Digital I/O | ✅ | ❌ | **Fan PWM** | ❌ |
| 18 | D18/SCK | SPI Clock | ✅ | ❌ | **TFT SCLK** | ❌ |
| 19 | D19/MISO | SPI Data In | ✅ | ❌ | **AVAILABLE** | ✅ |
| 21 | D21/SDA | I2C Data | ✅ | ❌ | **AVAILABLE** | ✅ |
| 22 | D22/SCL | I2C Clock | ✅ | ❌ | **AVAILABLE** | ✅ |
| 23 | D23/MOSI | SPI Data Out | ✅ | ❌ | **TFT MOSI** | ❌ |
| 25 | D25 | Digital I/O | ✅ | ✅ | **TFT RST** | ❌ |
| 34 | A2 | Analog Input | ❌ | ✅ | **AVAILABLE** | ✅ |
| 35 | A3 | Analog Input | ❌ | ✅ | **AVAILABLE** | ✅ |
| 36 | A0 | Analog Input | ❌ | ✅ | **Current Sensor** | ❌ |
| 39 | A1 | Analog Input | ❌ | ✅ | **AVAILABLE** | ✅ |

### **Reserved/Special Pins (DO NOT USE)**
| GPIO | Function | Notes |
|------|----------|-------|
| 0 | Boot Mode | Must be HIGH for normal boot |
| 1 | UART TX | Serial communication |
| 3 | UART RX | Serial communication |

### **Pins That DO NOT EXIST on FireBeetle ESP32-E**
❌ **These pins are found on other ESP32 variants but NOT on this board:**
- GPIO 26, 27, 32, 33 (commonly referenced but don't exist here)
- GPIO 6, 7, 8, 9, 10, 11 (internal flash pins)

> **Visual Reference:** ![FireBeetle ESP32-E Pinout](https://dfimg.dfrobot.com/enshop/image/data/DFR0654/pinout.png)

---

## 📋 Project Pin Usage & Future Expansion

### **Current Project Pin Assignments**
| Device/Function | GPIO | Pin Label | Type | Status | Notes |
|-----------------|------|-----------|------|--------|-------|
| DS18B20 Temperature | 15 | D15 | Digital (1-Wire) | ✅ Working | Temperature monitoring |
| Flame Sensor | 14 | D14 | Digital Input | ✅ Working | Fire detection |
| Fan PWM Control | 17 | D17 | Digital Output | ✅ Working | MOSFET gate control |
| RGB LED Red | 2 | D2 | Digital Output (PWM) | ✅ Fixed | Visual feedback |
| RGB LED Green | 4 | D4 | Digital Output (PWM) | ✅ Fixed | Visual feedback |
| RGB LED Blue | 13 | D13 | Digital Output (PWM) | ✅ Fixed | Visual feedback |
| TFT Display CS | 12 | D12 | Digital Output | ✅ Fixed | SPI Chip Select |
| TFT Display DC | 16 | D16 | Digital Output | ✅ Working | Data/Command (A0) |
| TFT Display RST | 25 | D25 | Digital Output | ✅ Working | Reset |
| TFT Display SDA | 23 | D23 | Digital Output | ✅ Fixed | Data line |
| TFT Display SCL | 18 | D18 | Digital Output | ✅ Fixed | Clock line |
| Current Sensor (Planned) | 36 | A0 | Analog Input | 🔄 Planned | SCT-013-000 |

### **Available Pins for Future Expansion**
| GPIO | Pin Label | Type | Capabilities | Best Use Case |
|------|-----------|------|--------------|---------------|
| 19 | D19 (MISO) | Digital I/O | PWM, SPI | SPI devices or general I/O |
| 21 | D21 (SDA) | Digital I/O | PWM, I2C | I2C sensors (BME280, RTC, etc.) |
| 22 | D22 (SCL) | Digital I/O | PWM, I2C | I2C sensors (BME280, RTC, etc.) |
| 34 | A2 | Analog Input | ADC only | Analog sensors (NTC, potentiometer) |
| 35 | A3 | Analog Input | ADC only | Analog sensors (NTC, potentiometer) |
| 39 | A1 | Analog Input | ADC only | Analog sensors (NTC, potentiometer) |

### **Pin Selection Guidelines for Future Development**
1. **Digital Sensors/Controls:** Use GPIO 19 (available digital pin)
2. **I2C Devices:** Use GPIO 21 (SDA) and 22 (SCL) - hardware I2C bus
3. **Analog Sensors:** Use GPIO 34, 35, 39 (input-only ADC pins)
4. **Additional SPI Devices:** Use GPIO 19 (MISO) with existing SPI bus
5. **PWM Outputs:** GPIO 12, 19, 21, 22 support PWM

### **Future Expansion Ideas**
- **Environmental Sensors:** BME280 (temp/humidity/pressure) via I2C
- **Real-Time Clock:** DS3231 RTC module via I2C
- **Additional Temperature:** NTC thermistors via analog pins
- **Servo Control:** Camera pan/tilt using PWM pins
- **Audio Detection:** Microphone module for print monitoring
- **Relay Control:** Additional fan or light control

---

## 🤝 Contributing

Ideas, feedback, and pull requests are welcome as the project grows!

---

## 📄 License

MIT License

---

## ⚡ Current Sensor (SCT-013-000) Integration

- **Type:** Non-invasive AC current sensor (SCT-013-000, 100A, 1V output)
- **Wiring:**
  - Cut or use a 3.5mm jack-to-terminal adapter to access the wires
  - Tip (Signal) → GPIO 36 (ESP32-E analog input)
  - Sleeve (GND) → GND rail
- **Usage:**
  - Reads analog voltage proportional to AC current
  - Use calibration and thresholds to detect printer states: RUN (high/variable current), PAUSE (steady, lower current), STOP (very low current)
  - Requires calibration for your specific setup
- **Note:** Vibration sensor skipped; may add a microphone module for redundant print status detection in the future.

