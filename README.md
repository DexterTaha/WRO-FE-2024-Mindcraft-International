MINDCRAFT WRO Future Engineers team
====

<p align="center">
  <img src="https://github.com/DexterTaha/WRO-2024-FUTURE-ENGINEERS/assets/130682580/d9385136-f971-4c95-ba80-ffc14f7c0a4e" alt="banner" width="1500">
</p>


This repository provides information and knowledge regarding the ongoing progress, evolution, and development of our self-driving robot vehicle, which was created and coded by us, [Salmane Derdeb](https://github.com/salmane-derdeb) and [Taha TAIDI LAAMIRI](https://github.com/DexterTaha), as participants in the Future Engineers 2024 division of the World Robot Olympiad (WRO).

## World Robot Olympiad (WRO)
<p align="center">
  <img src="https://github.com/DexterTaha/WRO-2024-FUTURE-ENGINEERS/assets/130682580/6d08f11e-2e99-4d6c-8994-0dc8783c6f05" width="1500">
</p>

The World Robot Olympiad (WRO) is a prestigious international robotics competition that ignites the imaginations of students worldwide. It challenges participants to showcase their creativity, problem-solving skills, and technical prowess in designing and programming robots for a variety of tasks and challenges.

One of the most dynamic categories within WRO is the Future Engineers category. Here, participants are tasked with developing innovative solutions to real-world problems using robotics and automation. This category serves as a breeding ground for future innovators, encouraging students to think critically and creatively, laying the groundwork for a new generation of engineers and technologists.

This year, the Future Engineers category presents an exciting challenge: creating a self-driving car. This challenge pushes participants to explore the cutting edge of robotics, adding layers of complexity and innovation to an already thrilling competition.

[Watch the challenge explanation video](https://www.youtube.com/watch?v=_J15lf6uhwo&t=2s)


## Content

- `t-photos`: Contains 2 photos of the team, including an official one and a funny photo with all team members.
- `v-photos`: Contains 6 photos of the vehicle, showcasing it from every side as well as from the top and bottom.
- `video`: Contains a `video.md` file with a link to a video demonstrating the vehicle's driving capabilities.
- `schemes`: Contains one or several schematic diagrams (JPEG, PNG, or PDF) illustrating all electromechanical components used in the vehicle, including electronic components and motors, and how they connect to each other.
- `src`: Contains the control software code for all components programmed to participate in the competition.
- `models` (optional): Contains files for models used by 3D printers, laser cutting machines, and CNC machines to produce the vehicle elements. If not needed, this directory can be removed.
- `other` (optional): Contains additional files that can help understand how to prepare the vehicle for the competition, such as documentation on connecting to a SBC/SBM, uploading files, datasets, hardware specifications, and communication protocols descriptions. If not needed, this directory can be removed.


# Robot Project Overview

## Table of Contents
1. [Project Overview](#project-overview)
   1.1. [Competition Context](#competition-context)  
   1.2. [Team Management](#team-management)  
   1.3. [Strengths and Limitations of Our Vehicle](#strengths-and-limitations-of-our-vehicle)  

2. [Technical Overview](#technical-overview)
   2.1. [Hardware Design](#hardware-design)  
       2.1.1. [Chassis](#chassis)  
       2.1.2. [Power and Control](#power-and-control)  
       2.1.3. [Sensors](#sensors)  
       2.1.4. [Wiring Diagram](#wiring-diagram)  
   2.2. [Software Design](#software-design)  
       2.2.1. [Programming Languages and Libraries](#programming-languages-and-libraries)  
       2.2.2. [Algorithm Documentation](#algorithm-documentation)  

3. [Programming Language and Libraries](#programming-language-and-libraries)  
   3.1. [Detecting Turns and Direction](#detecting-turns-and-direction)  
   3.2. [Lap Counting Method](#lap-counting-method)  
   3.3. [IMU-Based Steering](#imu-based-steering)  

4. [Open Challenge](#open-challenge-algorithm)  
   4.1. [Open Challenge Overview](#open-challenge-overview)  
   4.2. [PID Controller](#pid-controller)  
   4.3. [Turn Execution](#turn-execution)  

5. [Obstacle Avoidance Round Challenge](#obstacle-avoidance-round-challenge)  
   5.1. [Obstacle Challenge Overview](#obstacle-challenge-overview)  
   5.2. [Pillar Detection](#pillar-detection)  
   5.3. [Obstacle Avoidance Strategy](#obstacle-avoidance-strategy)  

6. [Designing Process](#designing-process)  
   6.1. [Steering System](#steering-system)  
   6.2. [Differential Gear](#differential-gear)  
   6.3. [Chassis](#chassis)  
   6.4. [Mechanism](#mechanism)  
   6.5. [Ackermann Steering Mechanism](#ackermann-steering-mechanism)  

7. [Power and Sense Management](#power-and-sense-management)  
   7.1. [Power Source](#power-source)  
   7.2. [Sensors We Used and Their Functions](#sensors-we-used-and-their-functions)  

8. [Hurdles and Challenges](#hurdles-and-challenges)  
   8.1. [Designing Process Challenges](#designing-process-challenges)  
   8.2. [Sensor and Coding Challenges](#sensor-and-coding-challenges)  
   8.3. [Mechanical Challenges](#mechanical-challenges)  

9. [Future Work](#future-work)  

10. [Acknowledgments](#acknowledgments)  

11. [Appendices](#appendices)  
    11.1. [Datasheets and Specifications](#datasheets-and-specifications)  
    11.2. [References](#references)  

12. [Reflections and Gratitude](#reflections-and-gratitude)  

## Project Overview

### Aim and Objectives
The primary aim of this robot project is to develop an autonomous vehicle capable of navigating its environment effectively. The key objectives include:

1. Detecting and avoiding obstacles in real-time.
2. Implementing autonomous driving capabilities.
3. Enabling state detection and automatic correction in case of errors.
4. Performing tasks efficiently within competition constraints.

### Competition Context
This robot is being developed for [insert competition name], where agility and responsiveness are critical for success.

### Team Management
Our team comprises skilled members with defined roles:

- **Team Leader:** [Name]
- **Software Developer:** [Name]
- **Hardware Engineer:** [Name]
- **Testing Specialist:** [Name]

### Strengths and Limitations of Our Vehicle
- **Strengths:** [List strengths here]
- **Limitations:** [List limitations here]

## Technical Overview

### Hardware Design

#### Chassis
The robot features a robust chassis designed for stability and maneuverability.

#### Power and Control
Utilizes a [specify battery type, e.g., LiPo] for power, coupled with an efficient motor driver setup.

#### Sensors
- **Distance Sensors:** [Types and functions]
- **Camera:** [Specifications]

#### Wiring Diagram
![Wiring Diagram](link-to-your-diagram.png)

### Software Design

#### Programming Languages and Libraries
Developed using Python and C++, with libraries such as OpenCV for computer vision.

#### Algorithm Documentation
Refer to [ALGORITHM.md](ALGORITHM.md) for detailed explanations of algorithms used.

## Programming Language and Libraries

### Detecting Turns and Direction
Description of the methodology for detecting turns and direction changes.

### Lap Counting Method
Explanation of the approach used for counting laps during the competition.

### IMU-Based Steering
Details on how the IMU (Inertial Measurement Unit) is utilized for steering control.

## Open Challenge

### Open Challenge Overview
Overview of the challenges faced during the competition and how they were approached.

### PID Controller
Description of the PID controller's role in maintaining vehicle stability and control.

### Turn Execution
Explanation of the methods used to execute turns effectively.

## Obstacle Avoidance Round Challenge

### Obstacle Challenge Overview
Overview of the obstacle avoidance challenge during the competition.

### Pillar Detection
Methods used for detecting pillars and other obstacles.

### Obstacle Avoidance Strategy
Strategies implemented for effective obstacle avoidance.

## Designing Process

### Steering System
Details on the steering system design and functionality.

### Differential Gear
Description of the differential gear system used in the robot.

### Chassis
Details about the chassis design process and considerations.

### Mechanism
Explanation of the mechanisms involved in the robot's movement.

### Ackermann Steering Mechanism
Overview of the Ackermann steering mechanism and its advantages.

## Power and Sense Management

### Power Source
Information about the power sources used in the robot.

### Sensors We Used and Their Functions
List of sensors and their respective roles in the robot's functionality.

## Hurdles and Challenges

### Designing Process Challenges
Challenges faced during the design process and how they were resolved.

### Sensor and Coding Challenges
Discussion of issues encountered with sensors and coding during development.

### Mechanical Challenges
Details of mechanical challenges faced during the building process.

## Future Work
Outline potential improvements and features for future iterations of the project.

## Acknowledgments
Thank those who contributed to the project, including mentors, team members, and supporters.

## Appendices

### Datasheets and Specifications
Provide links or references to datasheets for components used.

### References
Include references to any external resources or research papers relevant to the project.

## Reflections and Gratitude
Reflect on the learning experience and express gratitude to all contributors.

### Datasheets and Specifications
Provide links or references to datasheets for components used.

### References
Include references to any external resources or research papers relevant to the project.
