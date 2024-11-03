Here’s the updated Markdown documentation, clarifying that all components except the camera and LiDAR are connected to the Arduino Nano, while only the camera and LiDAR are connected to the Raspberry Pi.

---

# WRO-FE 2024 Mindcraft International Robot Circuit Documentation

This document provides a comprehensive overview of the robot circuit used for the World Robot Olympiad (WRO) Future Engineers 2024 competition. The circuit includes various components such as the Raspberry Pi, Arduino Nano, L298N motor driver, sensors, and power management elements. This guide covers the wiring, communication protocols, and component roles within the system.

![Robot Circuit Diagram](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/raw/main/schemes/Robot%20Circuit.png)

## Table of Contents

- [Components](#components)
- [Power Management](#power-management)
  - [7806 Voltage Regulator with Capacitors](#7806-voltage-regulator-with-capacitors)
  - [Buck Converter](#buck-converter)
- [Communication Protocols](#communication-protocols)
  - [I2C Communication](#i2c-communication)
  - [USB Serial Communication](#usb-serial-communication)
  - [UART Communication (TX/RX)](#uart-communication-tx-rx)
  - [PWM Signals](#pwm-signals)
- [Component Connections](#component-connections)
- [System Architecture and Data Flow](#system-architecture-and-data-flow)

---

## Components

The primary components in the circuit include:

1. **Raspberry Pi**: Main control and processing unit.
2. **Arduino Nano**: Microcontroller handling low-level sensor operations and communication with the Raspberry Pi.
3. **L298N Motor Driver**: Controls a 12V DC motor with magnetic encoders.
4. **12V DC Motor with Magnetic Encoders**: Drives the robot’s wheels, with encoder feedback for precise control.
5. **LiPo Battery (3S, 50C, 2.2Ah, 11.1V)**: High-capacity power source for the entire system.
6. **7806 Voltage Regulator**: Provides a stable 6V output for the servo motor.
7. **Two 470 µF Capacitors**: Connected to the 7806 for voltage stabilization and filtering.
8. **Buck Converter (11.1V to 5V)**: Supplies 5V power to the Raspberry Pi.
9. **DTOF (Distance Time-of-Flight) Sensors (I2C)**: Measures distances to obstacles.
10. **MPU6050 (Gyroscope/Accelerometer)**: Measures orientation and motion.
11. **Servo Motor**: Controls small actuators or sensor positioning.
12. **Buzzer**: Provides audio feedback.
13. **Camera Module**: Provides video input for image processing.
14. **LiDAR Sensor**: High-precision distance measurement for mapping or navigation.
15. **Switches**: Controls power delivery to different components manually.

---

## Power Management

### 7806 Voltage Regulator with Capacitors

The **7806 voltage regulator** is used to convert the LiPo battery voltage (11.1V) to a stable 6V output, powering the servo motor.

- **Input**: Connected to the 11.1V LiPo battery output.
- **Output**: Provides 6V for the servo motor.
- **Capacitors for Stabilization and Filtering**:
  - **Two 470 µF Capacitors** are connected to the 7806 voltage regulator to help stabilize the output voltage and filter out any noise. One capacitor is placed across the input and ground, and the other across the output and ground.
- **Grounding**: The 7806 ground pin connects to the shared ground of the entire circuit.

### Buck Converter (11.1V to 5V)

A **buck converter** steps down the 11.1V from the LiPo battery to a stable 5V to supply power to the Raspberry Pi.

- **Input**: Connected to the 11.1V LiPo battery.
- **Output**: Provides 5V power to the Raspberry Pi.
- **Grounding**: Connected to the common ground of the circuit.

---

## Communication Protocols

### I2C Communication

The **I2C protocol** is used to connect multiple sensors to the same bus, allowing communication with the Arduino Nano through two main lines: SCL (Clock) and SDA (Data). Each sensor has a unique address on the bus.

- **Components using I2C**:
  - **DTOF Sensors**: Four Time-of-Flight sensors for obstacle detection, each with a unique I2C address.
  - **MPU6050**: Provides data on orientation and movement.
- **Wiring**:
  - **SCL (Clock)**: Shared by all I2C devices, connected to the SCL pin on the Arduino.
  - **SDA (Data)**: Shared by all I2C devices, connected to the SDA pin on the Arduino.

### USB Serial Communication

**USB Serial Communication** is used for direct data transfer between the **Raspberry Pi** and **Arduino Nano**.

- The USB cable connects the Raspberry Pi and Arduino Nano, enabling bidirectional data transfer.

### UART Communication (TX/RX)

**UART (Universal Asynchronous Receiver/Transmitter)** is used for communication between the **LiDAR sensor** and **Raspberry Pi**.

- **Wiring**:
  - **TX (Transmit)** on the LiDAR to **RX (Receive)** on the Raspberry Pi.
  - **RX (Receive)** on the LiDAR to **TX (Transmit)** on the Raspberry Pi.

### PWM Signals

**PWM (Pulse Width Modulation)** signals are used to control both the motor driver and servo.

- **Motor Driver (L298N)**: Receives PWM signals from the Arduino Nano to adjust the speed of the 12V DC motor.
- **Servo Motor**: Controlled by the Arduino Nano using PWM for precise angle positioning.

---

## Component Connections

All components, except the camera and LiDAR, are connected to the **Arduino Nano**. This includes the motor driver, DTOF sensors, MPU6050, servo motor, and buzzer. The **Raspberry Pi** is only connected to the **camera module** (via the CSI port) and **LiDAR sensor** (via UART TX/RX), handling high-level processing and vision tasks.

### Raspberry Pi

- **GPIO**:
  - Communicates with the Arduino Nano via USB Serial.
  - Communicates with the LiDAR sensor via UART (TX/RX).
  - Powers the camera module for real-time image processing through the CSI port.

### Arduino Nano

- **I2C Bus**: Connects to the MPU6050 and Time-of-Flight distance sensors.
- **PWM**:
  - Controls the servo motor for actuation.
  - Drives the buzzer for audio signals.
- **GPIO for Motor Control**:
  - Connected to the L298N motor driver to control the 12V DC motor with PWM signals.

---

## System Architecture and Data Flow

1. **Power Supply**:
   - The LiPo battery (11.1V, 3S, 50C, 2.2Ah) provides power to high-current components like the motor driver and motor.
   - The 7806 voltage regulator, along with two 470 µF capacitors, supplies a stable 6V output to the servo motor.
   - The buck converter steps down the battery voltage to 5V to power the Raspberry Pi.

2. **Sensor Data Collection**:
   - The Arduino Nano collects data from all I2C sensors (MPU6050, DTOF sensors) and controls the motor, servo, and buzzer.
   - The data from these sensors is processed by the Arduino or transmitted to the Raspberry Pi via USB Serial.

3. **High-Level Processing**:
   - The Raspberry Pi performs high-level tasks such as video processing and complex decision-making.
   - Image data from the camera module is processed using computer vision libraries like OpenCV.
   - The Raspberry Pi receives distance data from the LiDAR sensor for navigation and obstacle avoidance.

4. **Control Flow**:
   - The Arduino Nano sends PWM signals to the L298N motor driver to control the 12V DC motor.
   - It also controls the servo motor and buzzer based on feedback from sensors.
   - The Raspberry Pi communicates with the Arduino Nano and sends additional commands as needed.

5. **Decision Making**:
   - Data from the LiDAR, DTOF sensors, and MPU6050 help in obstacle detection and path planning.
   - Based on this information, the Raspberry Pi and Arduino Nano coordinate actions, such as steering the robot or adjusting speed.

---

This circuit provides a robust foundation for an autonomous robot with sensing, communication, and motor control. By using both the Raspberry Pi and Arduino Nano, the system effectively distributes processing loads, with the Raspberry Pi focused on high-level vision and navigation and the Arduino Nano managing other essential components.

---
