# Raspberry Pi and Arduino Uno Color Detection Motor Control System

## Overview
This project enables color-based motor control using a Raspberry Pi and an Arduino Uno. The Raspberry Pi detects colors (red and green) in real time using OpenCV, sending commands to the Arduino Uno, which controls the motors accordingly. A dashboard provides a live preview of component states and allows configuration adjustments.

## Components and Connections

### 1. Arduino Uno
The Arduino Uno controls the motors based on serial commands received from the Raspberry Pi. It has functions to:
- Parse serial messages to determine motor actions
- Control motor speed and direction based on the received commands

#### Pin Configuration
| Component | Arduino Pin |
|-----------|-------------|
| Motor 1   | Pin X       |
| Motor 2   | Pin Y       |

### 2. Raspberry Pi
The Raspberry Pi processes video frames using OpenCV to detect specific colors in real time. It sends commands over serial to the Arduino Uno, instructing it to adjust motor actions based on detected colors.

- **Color Detection**: Uses OpenCV with HSV range filtering to detect red and green colors.
- **Command Structure**: Sends simple commands like `"MOVE_FORWARD"`, `"TURN_LEFT"`, etc., to the Arduino based on detected colors.

### 3. Serial Communication
The Raspberry Pi and Arduino communicate via a serial connection, with the following protocol:
- **Baud Rate**: 9600
- **Command Format**: Commands are sent as strings, e.g., `"MOVE_FORWARD"`, `"STOP"`.
- **Error Handling**: Ensures that messages are acknowledged before sending the next command.

## Dashboard
The dashboard provides a visual interface to monitor and control the system's state.

### Dashboard Features
- **Color Detection Preview**: Displays the live feed with color masks for red and green objects.
- **Motor State Display**: Shows the current state of each motor, e.g., running or stopped.
- **Serial Connection Status**: Indicates if the connection between the Raspberry Pi and Arduino is active.
- **Adjustable Parameters**: Allows the user to tweak HSV values for color detection and update motor controls.

### Preview
The dashboard displays each component’s status in real time, providing feedback on:
- Detected color regions
- Motor activity based on color triggers
- Connection status between Raspberry Pi and Arduino

## Code Structure

### Raspberry Pi Code
The Raspberry Pi code includes:
- Color detection functions using OpenCV
- Serial communication setup and message-sending functions
- Main loop for processing frames and sending commands to Arduino

### Arduino Code
The Arduino code includes:
- Serial message reading and parsing
- Motor control functions for each command received
- Error handling for lost or malformed commands

## How to Run the System

1. **Connect Components**: Ensure the Raspberry Pi is connected to the Arduino over serial.
2. **Upload Arduino Code**: Upload the motor control code to the Arduino.
3. **Run Raspberry Pi Code**: Execute the color detection script on the Raspberry Pi.
4. **Open Dashboard**: Access the dashboard to monitor and control the system.

## Troubleshooting
- **No Serial Connection**: Check the wiring and ensure the baud rate matches on both devices.
- **Color Detection Issues**: Adjust HSV values on the dashboard.
- **Motor Control Issues**: Verify Arduino pin connections and motor control functions.

## Future Improvements
- Add more colors for multi-condition control
- Implement more complex motor control logic for smoother movements
- Refine the dashboard to include data logging

---

**Project Authors**: Salmane and the Mindcraft team
