# 🚧 Coal Mine Safety Monitoring System

An IoT-based real-time environmental monitoring system designed to improve safety in underground coal mines using Arduino Uno, LoRa communication, and multiple environmental sensors.

---

## 📌 Overview

Underground coal mines are hazardous environments where gas leaks, excessive temperature, and abnormal vibrations can pose serious risks to miners.

This project continuously monitors critical environmental parameters and wirelessly transmits sensor data using LoRa technology, enabling early detection of hazardous conditions and improving mine safety.

---

## 🎯 Objectives

- Monitor environmental conditions in real time
- Detect hazardous gas levels
- Monitor temperature and vibration
- Enable long-range wireless communication using LoRa
- Trigger alarms when safety thresholds are exceeded

---

## 🛠 Hardware Components

- Arduino Uno
- LoRa Module
- MQ-2 Gas Sensor
- MPU6050 Accelerometer & Gyroscope
- LM393 Vibration Sensor
- Buzzer
- Jumper Wires
- Breadboard
- Power Supply

---

## 💻 Software Used

- Arduino IDE
- Embedded C / Arduino Programming

---

## ⚙ Working Principle

The transmitter unit continuously collects data from environmental sensors connected to the Arduino Uno.

The collected sensor readings are transmitted wirelessly through the LoRa module.

The receiver unit receives the transmitted data, displays the environmental parameters, and activates a buzzer whenever predefined safety thresholds are exceeded.

---

## 📂 Repository Structure

```
Coal-Mine-Safety-Monitoring-System
│
├── transmitter
│   └── transmitter.ino
│
├── receiver
│   └── receiver.ino
│
├── Project_Report.pdf
│
├── README.md
│
└── LICENSE
```

---

## 🚀 Features

- Real-time environmental monitoring
- Long-range LoRa communication
- Hazard detection using threshold values
- Low-cost embedded solution
- Modular transmitter and receiver architecture

---

## 🔮 Future Improvements

- Cloud-based monitoring dashboard
- GSM/SMS emergency alerts
- Mobile application integration
- GPS tracking for rescue operations
- Machine learning for predictive hazard analysis

---

## 👩‍💻 Author

**D. S. K. Manognya**

B.Tech Electronics and Communication Engineering

BVRIT Hyderabad College of Engineering for Women

---

## 📜 License

This project is licensed under the MIT License.
