Smart Motorbike Locking System

Overview

A smart motorbike locking and security system developed using an Arduino UNO R4 WiFi and Raspberry Pi. The system uses weight sensing to automatically detect when a motorbike is present, engage two servo-controlled locks, and monitor for changes in weight that could indicate tampering.

How It Works

1. An HX711 load cell amplifier measures the weight applied to the system.
2. When the detected weight remains above a defined threshold for 2 seconds, the system automatically locks.
3. Two servo motors operate the locking mechanism.
4. While locked, the system continuously monitors the measured weight.
5. A significant change in weight triggers an alarm state.
6. An LED and buzzer provide visual and audible alarm indications.
7. The Arduino connects to Wi-Fi and communicates using MQTT.
8. An MQTT release command can remotely release the locks and reset the alarm.

Hardware

* Arduino UNO R4 WiFi
* Raspberry Pi
* HX711 load cell amplifier
* Load cell
* 2× Servo motors
* 16×2 I2C LCD
* LED
* Buzzer

Software & Technologies

* Arduino C/C++
* Python / Raspberry Pi
* MQTT
* Wi-Fi
* HX711 load-cell library
* Servo control
* I2C communication

Key Features

* Automatic weight-based locking
* Dual servo locking mechanism
* Weight-change tamper detection
* Audible and visual alarm
* LCD system-status display
* Wi-Fi connectivity
* MQTT remote release
* Non-blocking alarm operation using millis()

Learning Outcomes

This project provided practical experience in embedded systems, sensor integration, servo control, wireless communication, MQTT, state-machine programming, and IoT system development.
