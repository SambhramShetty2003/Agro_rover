# Agro Rover 🚜🌱

## Overview

**Agro Rover** is a smart, autonomous, and modular agricultural robot developed as our final-year major project. Designed to assist farmers in performing repetitive tasks efficiently, the Agro Rover is capable of performing various functions like soil monitoring, seeding, pesticide spraying, and real-time data collection.

Our aim is to contribute to the modernization of agriculture by integrating robotics and IoT for enhanced productivity and sustainability.

---

## Features

- 🌱 **Soil Monitoring**: Measures moisture, temperature, and pH levels. (https://docs.google.com/spreadsheets/d/e/2PACX-1vRyNmdbRcTDtKLtjzVX6yAA7jjKX55YSQ39X1qZlaA9dLxywMsRLFFrLsGcFwDLHCorP9yb10JPRGsQ/pubhtml)
- 🛰️ **GPS and Vision Navigation**: Autonomous path-following using GPS and sensor fusion.
- 📡 **IoT Dashboard**: Real-time data visualization and control via web interface.

---

## Technologies Used

- **Microcontroller**: Arduino Uno / ESP32 / NodeMcu(based on actual choice)
- **Sensors**: Soil moisture, pH sensor, temperature sensor, ultrasonic for obstacle detection
- **Motors**: DC Geared Motors with Motor Driver
- **Power**:  Battery setup (12v DC 2200mAH)
- **Connectivity**: WiFi / Bluetooth for remote monitoring
- **Software Stack**:
  - Embedded C / Arduino IDE
  - Python (for dashboard or backend, if used)
  - HTML/CSS/JAVASCRIPT (for IoT Dashboard, if applicable)

---

## System Architecture

```plaintext
[Soil Sensors] → [Microcontroller] → [Motor Control & Actuators]
                                 ↓
                        [Wireless Module]
                                 ↓
                       [IoT Dashboard / App]
