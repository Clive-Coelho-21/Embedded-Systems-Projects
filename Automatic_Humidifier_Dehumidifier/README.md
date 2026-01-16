# Automatic Humidifier Dehumidifier Version 1

## Components Used:
1. ESP-32  
2. 16x2 Liquid Crystal Display (LCD) with I2C Module  
3. DHT22  
4. 2-Channel Relay  

## Software Used:
1. Arduino IDE

## Problem Statement
The Automatic Humidifier & Dehumidifier System is designed for residential environments to maintain optimal humidity levels efficiently.

- When humidity is high, the system activates a dehumidifier instead of an AC, reducing electricity usage.

- When humidity is low, the system activates a humidifier to improve comfort and air quality.

- An ESP32 with a humidity sensor continuously monitors the environment and makes autonomous control decisions.

## Working

The ESP32 samples temperature and humidity at 0.5 Hz using the DHT22 sensor and displays the values on an I2C LCD.

### Humidity Control (Hysteresis-Based)

To avoid frequent ON–OFF switching, hysteresis is used:

- Dehumidifier

  - ON when humidity ≥ 70%

  - OFF when humidity ≤ 65%

- Humidifier

  - ON when humidity ≤ 30%

  - OFF when humidity ≥ 35%

Only one device operates at a time, ensuring stable and efficient control.

### Power Management (Motion-Based)

- A PIR sensor is used to wake the ESP32 from deep sleep.

- When motion is detected, the system becomes active and continues monitoring humidity.

- If no motion is detected for 2 minutes, the ESP32 returns to deep sleep to minimize power consumption.

- This approach ensures energy efficiency, stable humidity regulation, and low-power operation, making the system suitable for residential use and academic demonstration.
---

# Automatic Humidifier Dehumidifier Version 2

## Components Used:
1. ESP-32  
2. DHT22  
3. 2-Channel Relay  

## Software Used:
1. Arduino IDE
2. Blynk IOT App on Android and Web Dashboard

## Working (IoT Mode – Blynk)

The ESP32 samples temperature and humidity at 0.5 Hz using the DHT22 sensor and sends the data to the Blynk dashboard, where values are displayed on gauges.

### Control Modes

The system supports Auto and Manual modes, selectable from the Blynk app.

**Auto Mode (Hysteresis Control)**

The ESP32 automatically controls the devices based on humidity:

- Dehumidifier

  - ON when humidity ≥ 70%

  - OFF when humidity ≤ 65%

- Humidifier

  - ON when humidity ≤ 30%

  - OFF when humidity ≥ 35%

Hysteresis prevents rapid switching and ensures stable operation.

**Manual Mode**

- The user directly controls the humidifier and dehumidifier using Blynk buttons.

- Sensor data remains visible, but automatic control is disabled.

This mode allows full user control while retaining real-time environmental monitoring.