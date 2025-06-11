# Bambu Lab A1 Enclosure Smart Monitor

A smart, WiFi-enabled monitoring and control system for your Bambu Lab A1 3D printer enclosure. This project aims to improve safety, convenience, and insight for your 3D printing setup by tracking temperature, detecting hazards, and automating cooling—all viewable from a simple web dashboard.

---

## 🚀 Project Overview

This project uses an ESP32S3 CAM module as the main controller to monitor and control the environment inside your 3D printer enclosure. The system is designed to:

- **Monitor temperature** inside the enclosure.
- **Detect fire, vibration, and electrical current** for safety and diagnostics.
- **Automatically control cooling fans** to protect electronics.
- **Display real-time data** on a web dashboard accessible from any device.
- **Log events and errors** for easy troubleshooting.
- **Support wireless firmware updates** and future sensor expansion.

---

## 🛠️ Hardware Setup (Current Stage)

You're just getting started! Here's your current setup:

- **ESP32S3 CAM** module placed on a breadboard.
- **Power rails:**  
  - Left rail: 5V (from BEC, for ESP32 and sensors)  
  - Right rail: 24V (from printer AMS port, for fans)
- **Common ground**: All GNDs tied together.

**Next steps:**  
Add sensors (temperature, flame, vibration, current), display, and fans as you progress.

---

## 🧰 Planned Components

- **ESP32S3 CAM** – Main controller (WiFi, Bluetooth, camera)
- **NTC Temperature Sensor** – Monitors enclosure temperature
- **Flame Sensor** – Fire safety
- **SCT013 Current Sensor** – Power monitoring
- **ST7735S 128x128 RGB TFT** – Local status display
- **Vibration Sensor** – Print status detection
- **2x 24V Fans** – Active cooling
- **5V BEC** – Power regulation from 24V AMS port

---

## 🖥️ Features (Planned)

- Real-time temperature and status monitoring
- Automatic fan control based on temperature
- Fire and vibration detection
- Power usage monitoring
- Web dashboard for live data and logs
- Wireless firmware updates (OTA)
- Modular for future sensor/feature expansion

---

## 📦 Getting Started

1. **Breadboard your ESP32S3 CAM** and connect 5V/24V rails as described above.
2. **Connect to your computer** via USB for programming.
3. **(Coming soon)**: Firmware, wiring diagrams, and dashboard setup instructions.

---

## 📚 ESP32S3 CAM Board Specs

- Dual-core 32-bit LX6 CPU (up to 240MHz)
- 520KB SRAM, 4MB PSRAM, 32Mbit SPI flash
- WiFi 802.11 b/g/n, Bluetooth 4.2 LE
- Camera support (OV2640/OV7670)
- MicroSD slot, LED flash, expansion headers
- Power: 5V via pin header
- Deep sleep: 6mA, Active: 180–310mA

---

## 🧩 Pinout Reference

For wiring and hardware reference, see the ESP32-CAM pinout diagram:

![ESP32-CAM Pinout](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/03/ESP32-CAM-pinout-new.png?quality=100&strip=all&ssl=1)

> **Note:** Your board is almost the same as this diagram, except it includes a USB port for easier programming and serial monitoring.

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

## 🧮 Available GPIO Pins (No SD Card)

With the SD card not used, the following GPIOs are typically available for sensors and peripherals:
- **GPIO 12, 13, 14, 15, 16** (general purpose, check for camera conflicts)
- **GPIO 2, 4** (GPIO4 is also used for the onboard flash LED)
- **GPIO 0** (used for flashing, avoid for permanent sensors)
- **GPIO 34, 35, 36, 39** (input-only, ideal for analog sensors)

**Note:** Always check your camera configuration for any pin conflicts.

### Suggested Pin Assignments

| Device           | Suggested Pin | Notes                        |
|------------------|--------------|------------------------------|
| Vibration Sensor | GPIO 13      | Digital input                |
| DS18B20 Temp     | GPIO 15      | 1-Wire bus                   |
| Flame Sensor     | GPIO 14      | Digital or analog input      |
| TFT Display      | GPIO 12, 16, 2, 4 | SPI: SCK, MOSI, CS, DC, RESET |
| Current Sensor   | GPIO 36      | Analog input (input-only)    |

**Tip:** DS18B20 can share its pin with other 1-Wire sensors if needed.

---

## 📝 Roadmap

- [x] ESP32S3 CAM breadboarded and powered
- [ ] Add temperature sensor
- [ ] Add flame and vibration sensors
- [ ] Add current sensor
- [ ] Add TFT display
- [ ] Develop web dashboard
- [ ] Implement fan control logic
- [ ] Add OTA updates

---

## 🤝 Contributing

Ideas, feedback, and pull requests are welcome as the project grows!

---

## 📄 License

MIT License