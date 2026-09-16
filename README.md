Smart Motorbike Locking System

Overview

A connected motorbike security system developed using an Arduino UNO R4 WiFi and Raspberry Pi. The system combines weight sensing, servo-controlled locking, MQTT communication, and a Node-RED dashboard to provide both automatic and remote control of the locking system.

System Architecture

The Arduino UNO R4 WiFi acts as the embedded control system. It monitors a load cell through an HX711 amplifier and controls two servo motors, an LCD, LED, and buzzer.

The Raspberry Pi hosts the system server and MQTT communication, acting as the link between the Arduino and the user interface. Node-RED processes the MQTT messages through JSON-based flows and provides a visual dashboard that allows the user to remotely lock or unlock the motorbike.

How It Works

* A load cell measures the weight applied to the locking system.
* When a sufficient and stable weight is detected, the Arduino automatically engages the two servo locks.
* The system continuously monitors the weight while locked.
* A significant change in weight triggers the alarm, activating the buzzer and LED.
* The Arduino communicates with the Raspberry Pi using Wi-Fi and MQTT.
* The Raspberry Pi hosts the Node-RED dashboard, providing an onscreen interface for controlling the lock.
* Pressing the lock/unlock controls on the dashboard sends MQTT commands back to the Arduino.
* The LCD provides local status information such as UNLOCKED, LOCKED, and ALARM.

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
* Node-RED
* MQTT
* JSON
* Wi-Fi
* I2C
* Embedded systems

Key Features

* Automatic weight-based locking
* Remote locking and unlocking
* Weight-based tamper detection
* Audible and visual alarm
* Real-time system status
* Web-based Node-RED dashboard
* MQTT communication between embedded and server systems
* Integration of hardware, networking, and software into a single IoT system

Skills Demonstrated

This project developed practical experience in embedded programming, IoT architecture, sensor integration, MQTT communication, Node-RED, JSON data flows, Raspberry Pi server configuration, servo control, and hardware/software integration.
