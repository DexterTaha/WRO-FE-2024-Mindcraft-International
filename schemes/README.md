Certainly! Here’s a comprehensive Markdown document for the circuit, explaining the components, communication protocols, wiring, and architecture based on the `.fzz` file from the provided GitHub repository and the provided circuit image.

---

# WRO-FE 2024 Mindcraft International Robot Circuit Documentation

This document provides a detailed explanation of the robot circuit used for the World Robot Olympiad (WRO) Future Engineers 2024 competition. The circuit includes various components like the Raspberry Pi, Arduino Nano, L298N motor driver, sensors, and power management elements. It demonstrates the wiring, communication protocols, and component roles within the system.

## Table of Contents

- [Components](#components)
- [Power Management](#power-management)
  - [7805 Voltage Regulator](#7805-voltage-regulator)
- [Communication Protocols](#communication-protocols)
  - [I2C Communication](#i2c-communication)
  - [UART Communication](#uart-communication)
  - [PWM Signals](#pwm-signals)
- [Component Connections](#component-connections)
- [System Architecture and Data Flow](#system-architecture-and-data-flow)

---

## Components

The primary components in the circuit include:

1. **Raspberry Pi**: Main control and processing unit.
2. **Arduino Nano**: Microcontroller handling low-level sensor operations and communication with the Raspberry Pi.
3. **L298N Motor Driver**: Controls a DC motor's direction and speed.
4. **DC Motor**: Drives the robot’s wheels or actuators.
5. **LiPo Batteries (3.7V, 1000mAh)**: Power source for the entire system.
6. **7805 Voltage Regulator**: Provides stable 5V power to components.
7. **Time-of-Flight Distance Sensors (I2C)**: Measures distances to obstacles.
8. **MPU6050 (Gyroscope/Accelerometer)**: Measures orientation and motion.
9. **Ultrasonic Sensor**: Additional distance measurement sensor.
10. **Servo Motor**: Controls small actuators or sensor positioning.
11. **Buzzer**: Provides audio feedback.
12. **Camera Module**: Provides video input for image processing.
13. **LiDAR Sensor**: High-precision distance measurement for mapping or navigation.
14. **Switches**: Controls power delivery to different components manually.

---

## Power Management

### 7805 Voltage Regulator

The **7805 voltage regulator** is used to convert the LiPo battery voltage (higher than 5V) to a stable 5V output. The 7805 powers the Arduino Nano and any 5V components, ensuring stable operation.

- **Input**: Connected to the LiPo battery output.
- **Output**: Provides 5V for the Arduino Nano, sensors, and other low-voltage components.
- **Grounding**: The 7805 ground pin connects to the shared ground of the entire circuit.

---

## Communication Protocols

### I2C Communication

The **I2C protocol** is used to connect multiple sensors to the same bus, allowing communication with the Arduino Nano through two main lines: SCL (Clock) and SDA (Data). Each sensor has a unique address on the bus.

- **Components using I2C**:
  - **Time-of-Flight Sensors**: Each sensor has a unique I2C address to avoid conflicts.
  - **MPU6050**: Provides data on orientation and movement.
- **Wiring**:
  - **SCL (Clock)**: Shared by all I2C devices, connected to the SCL pin on the Arduino.
  - **SDA (Data)**: Shared by all I2C devices, connected to the SDA pin on the Arduino.

### UART Communication

**UART (Universal Asynchronous Receiver/Transmitter)** enables serial communication between the **Raspberry Pi** and **Arduino Nano**.

- **Wiring**:
  - **TX (Transmit)** on the Arduino to **RX (Receive)** on the Raspberry Pi.
  - **RX (Receive)** on the Arduino to **TX (Transmit)** on the Raspberry Pi.

### PWM Signals

**PWM (Pulse Width Modulation)** signals are used to control both the motor driver and servo.

- **Motor Driver (L298N)**: Receives PWM signals from the Raspberry Pi to adjust the speed of the DC motor.
- **Servo Motor**: Connected to the Arduino Nano, controlled by PWM for precise angle positioning.

---

## Component Connections

### Raspberry Pi

- **GPIO**:
  - Connected to the L298N motor driver to control motor direction and speed.
  - Communicates with the Arduino Nano via UART.
  - Powers the camera module for real-time image processing.

### Arduino Nano

- **I2C Bus**: Connects to the MPU6050 and Time-of-Flight distance sensors.
- **PWM**:
  - Controls the servo motor for actuation.
  - Drives the buzzer for audio signals.

### L298N Motor Driver

- **Inputs**: Receives PWM signals from the Raspberry Pi to control motor speed and direction.
- **Outputs**: Connects to the DC motor.

### Sensors and Actuators

1. **Time-of-Flight Distance Sensors**: Communicate with the Arduino Nano over I2C to measure distance.
2. **MPU6050**: Communicates with the Arduino Nano over I2C for orientation and motion data.
3. **Ultrasonic Sensor**: Measures distance by emitting sound waves and calculating the time taken for reflection.
4. **Servo Motor**: Controlled by the Arduino Nano using PWM.
5. **Camera Module**: Captures video, connected to the Raspberry Pi.
6. **LiDAR Sensor**: Provides high-precision distance measurements to the Raspberry Pi.

---

## System Architecture and Data Flow

1. **Power Supply**:
   - The LiPo batteries provide power to high-current components like the motor driver and motor.
   - The 7805 voltage regulator supplies a stable 5V output to the Arduino Nano and 5V sensors.

2. **Sensor Data Collection**:
   - The Arduino Nano collects data from the I2C sensors (MPU6050, Time-of-Flight sensors) and the ultrasonic sensor.
   - The data from these sensors is processed by the Arduino or transmitted to the Raspberry Pi via UART.

3. **High-Level Processing**:
   - The Raspberry Pi performs high-level tasks such as video processing and complex decision-making.
   - Image data from the camera module is processed using computer vision libraries like OpenCV.
   - Based on the sensor and image data, the Raspberry Pi sends control commands to the motor driver.

4. **Control Flow**:
   - The Raspberry Pi sends PWM signals to the L298N motor driver to control the DC motor.
   - The Arduino Nano sends PWM signals to the servo motor and the buzzer for actuation and audio alerts.

5. **Decision Making**:
   - Data from the LiDAR, ultrasonic sensor, and Time-of-Flight sensors helps in obstacle detection and path planning.
   - Based on this information, the Raspberry Pi and Arduino Nano coordinate actions, such as steering the robot or adjusting speed.

---

This circuit provides a robust foundation for an autonomous robot with sensing, communication, and motor control. By using both the Raspberry Pi and Arduino Nano, the system effectively distributes processing loads, enabling efficient sensor management and real-time decision-making.
