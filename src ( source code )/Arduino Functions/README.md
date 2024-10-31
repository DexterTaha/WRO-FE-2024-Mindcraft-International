# Arduino Robot Control Code Documentation

This README provides a detailed explanation of the Arduino code used to control a robot equipped with distance sensors, a steering mechanism, and communication with a Raspberry Pi. The code manages motor control, steering, sensor data acquisition, and communication between the Arduino and Raspberry Pi.

## Table of Contents

1. [Overview](#overview)
2. [Hardware Components](#hardware-components)
3. [Pin Configuration](#pin-configuration)
4. [Library Dependencies](#library-dependencies)
5. [Code Structure](#code-structure)
6. [Functions Explanation](#functions-explanation)
    - [Interrupt Service Routines (ISRs)](#interrupt-service-routines-isrs)
    - [Encoder Functions](#encoder-functions)
    - [Motor Control Functions](#motor-control-functions)
    - [Sensor Setup and Reading Functions](#sensor-setup-and-reading-functions)
    - [Buzzer Functions](#buzzer-functions)
    - [Communication Functions](#communication-functions)
    - [Utility Functions](#utility-functions)
7. [Setup and Initialization](#setup-and-initialization)
8. [Main Loop Execution](#main-loop-execution)
9. [Wiring Diagram](#wiring-diagram)
10. [How to Use](#how-to-use)
11. [Troubleshooting](#troubleshooting)
12. [License](#license)

---

## Overview

The provided Arduino code is designed to control a robot with the following features:

- **Motor Control**: Controls the speed and direction of the robot using an L298N motor driver.
- **Steering Mechanism**: Uses a servo motor for steering control.
- **Distance Sensing**: Utilizes four VL53L1X distance sensors for obstacle detection in all directions (front, back, left, right).
- **Encoder Feedback**: Reads encoder data to monitor motor speed and distance traveled.
- **Communication**: Exchanges data with a Raspberry Pi for higher-level processing and decision-making.
- **Buzzer Alerts**: Provides audible feedback for different robot states (start, stop, error).

---

## Hardware Components

- **Arduino Uno** (or compatible microcontroller)
- **L298N Motor Driver**
- **DC Motor** with encoder
- **Servo Motor** for steering (connected to pin 10)
- **VL53L1X Distance Sensors** (x4) for front, back, left, and right detection
- **Buzzer** (connected to pin 8)
- **Switch** (connected to analog pin A0)
- **Raspberry Pi 4 Model B** (for data processing and control commands)
- **Miscellaneous**: Resistors, wires, breadboard or PCB, connectors

---

## Pin Configuration

| Component                | Arduino Pin |
|--------------------------|-------------|
| L298N EN_A (Speed)       | 11          |
| L298N IN1 (Direction)    | 13          |
| L298N IN2 (Direction)    | 12          |
| Steering Servo           | 10          |
| Encoder Channel A        | 2           |
| Encoder Channel B        | 3           |
| Buzzer                   | 8           |
| Switch                   | A0          |
| VL53L1X XSHUT Pins       | 4, 5, 6, 7  |
| Gyroscope (example)      | A2          |

---

## Library Dependencies

Ensure you have the following libraries installed in your Arduino IDE:

- **Servo.h**: For controlling the servo motor.
- **VL53L1X.h**: For interfacing with the VL53L1X distance sensors.
- **Wire.h**: For I2C communication with sensors.

---

## Code Structure

The code is organized into several sections:

1. **Variable and Constant Definitions**: Pin assignments, sensor configurations, and control variables.
2. **Interrupt Service Routines (ISRs)**: Functions to handle encoder pulses.
3. **Initialization Functions**: Setup functions for the encoder, sensors, and initial states.
4. **Motor Control Functions**: Functions to control motor speed and direction.
5. **Sensor Functions**: Functions to read data from the VL53L1X sensors.
6. **Buzzer Functions**: Functions to produce different sounds for various robot states.
7. **Communication Functions**: Functions to send data to and receive commands from the Raspberry Pi.
8. **Main Loop**: The `loop()` function that runs continuously, handling the robot's operation based on the switch state.

---

## Functions Explanation

### Interrupt Service Routines (ISRs)

- **encoderISR_A()**: Increments the encoder count when a pulse is detected on Channel A.
- **encoderISR_B()**: Decrements the encoder count when a pulse is detected on Channel B (if using quadrature encoding).

### Encoder Functions

- **setupEncoder()**: Initializes the encoder pins and attaches the ISRs.
- **readEncoder()**: Returns the current encoder count.
- **resetEncoder()**: Resets the encoder count to zero.

### Motor Control Functions

- **driveDistanceSpeed(float distanceCM, int speedInput)**: Moves the robot a specified distance in centimeters at a given speed percentage (-100 to 100). It uses encoder feedback to determine when the desired distance has been traveled.
- **controlRobot(int speedInput, int steeringInput)**: Controls the robot's speed and steering based on inputs received (e.g., from the Raspberry Pi). Speed input ranges from -100 (full reverse) to 100 (full forward). Steering input ranges from -100 (full left) to 100 (full right).
- **StopMotors()**: Stops the motor by setting the control pins to LOW and speed to zero.
- **HoldMotors()**: Engages both motor control pins to HIGH to hold the motor position (dynamic braking).

### Sensor Setup and Reading Functions

- **setupSensors()**: Initializes the VL53L1X distance sensors by configuring their XSHUT pins and setting unique I2C addresses.
- **readAndPrintDistances()**: Reads distances from all sensors and prints them to the Serial monitor.

### Buzzer Functions

- **BuzzerRobotStart()**: Plays a startup sound when the robot is powered on or initialized.
- **BuzzerRobotEnd()**: Plays a shutdown sound when the robot operation ends.
- **BuzzerRobotError()**: Plays an error sound when an issue is detected (e.g., switch is off).
- **BuzzerRobotSpecial()**: Plays a special melody (optional use).

### Communication Functions

- **sendDataToPi()**: Sends sensor readings and motor speed data to the Raspberry Pi via Serial communication.
- **receiveDataFromPi()**: Receives control commands from the Raspberry Pi and parses them to control the robot.

### Utility Functions

- **isSwitchOn(int value)**: Determines if the switch is in the "on" position based on the analog reading.
- **act()**: Performs the main actions of sending data to and receiving commands from the Raspberry Pi.

---

## Setup and Initialization

1. **Serial Communication**: Begins Serial communication at 115200 baud rate for communication with the Raspberry Pi.
2. **I2C Communication**: Initializes the I2C bus for communication with the distance sensors.
3. **Pin Modes**: Sets the appropriate pin modes for motor control, buzzer, and switch.
4. **Servo Initialization**: Attaches the steering servo to the designated pin.
5. **Motor and Encoder Initialization**: Ensures motors are stopped and encoders are set up.
6. **Sensor Initialization**: Calls `setupSensors()` to initialize all distance sensors.
7. **Startup Sound**: Plays the startup sound using `BuzzerRobotStart()`.

---

## Main Loop Execution

The `loop()` function continuously performs the following steps:

1. **Switch State Check**: Reads the switch value to determine if the robot should operate.
2. **Operation Execution**:
   - If the switch is on (`isSwitchOn(switchValue)` returns `true`), it calls the `act()` function to handle communication and control.
   - If the switch is off, it stops the motors (`HoldMotors()`) and plays an error sound (`BuzzerRobotError()`).

---

## Wiring Diagram

**Note**: Please refer to the pin configuration section and ensure all components are connected according to the assigned pins. A wiring diagram would typically be provided here, but since this is a text-based format, please ensure:

- **Motors**: Connected to the L298N motor driver, which is then connected to the Arduino pins `ENA`, `IN_1`, and `IN_2`.
- **Encoder**: Encoder channels A and B connected to pins `2` and `3`.
- **Servo Motor**: Signal wire connected to pin `10`.
- **VL53L1X Sensors**: Each sensor's XSHUT pin connected to pins `4`, `5`, `6`, and `7`. SDA and SCL connected to Arduino's SDA and SCL pins.
- **Buzzer**: Positive pin connected to pin `8`, negative pin connected to ground.
- **Switch**: One side connected to analog pin `A0`, the other side connected to `5V`, with a pull-down resistor connected to ground if necessary.
- **Raspberry Pi**: Connected via Serial communication to the Arduino (ensure voltage levels are compatible or use a logic level converter).

---

## How to Use

1. **Hardware Setup**: Assemble the robot according to the wiring diagram and ensure all connections are secure.
2. **Library Installation**: Install all required libraries in the Arduino IDE.
3. **Upload Code**: Load the provided code into the Arduino IDE and upload it to the Arduino board.
4. **Power On**: Turn on the robot. The startup sound should play.
5. **Switch Activation**: Flip the switch connected to pin `A0` to the "on" position to enable robot operation.
6. **Raspberry Pi Connection**: Ensure the Raspberry Pi is connected and running the appropriate code to send control commands and receive sensor data.
7. **Operation**: The robot will begin operating based on commands from the Raspberry Pi, moving, steering, and avoiding obstacles as programmed.

---

## Troubleshooting

- **No Movement**: If the robot doesn't move, check motor connections and ensure the motor driver is properly connected.
- **Sensors Not Responding**: Verify the connections of the VL53L1X sensors and ensure their addresses are correctly set.
- **Buzzer Not Sounding**: Check the buzzer connections and ensure it is connected to the correct pin.
- **Serial Communication Issues**: Ensure the baud rate matches on both the Arduino and Raspberry Pi. Check connections.
- **Switch Not Working**: Verify the switch is correctly connected and functioning. Use a multimeter to test continuity.

---

## License

This project is open-source and free to use under the MIT License.

---

**Note**: Always ensure safety when operating robots. Keep clear of moving parts, and disconnect power when making adjustments or modifications.
