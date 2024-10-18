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
   - [Aim and Objectives](#aim-and-objectives)
   - [Competition Context](#competition-context)
   - [Team Management](#team-management)
2. [Technical Overview](#technical-overview)
   - [Hardware Design](#hardware-design)
     - [Chassis](#chassis)
     - [Power and Control](#power-and-control)
     - [Sensors](#sensors)
     - [Wiring Diagram](#wiring-diagram)
   - [Software Design](#software-design)
     - [Programming Languages and Libraries](#programming-languages-and-libraries)
     - [Algorithm Documentation](#algorithm-documentation)
3. [Functional Capabilities](#functional-capabilities)
   - [Obstacle Detection and Avoidance](#obstacle-detection-and-avoidance)
   - [Color Detection](#color-detection)
   - [Navigation and Movement](#navigation-and-movement)
4. [Challenges and Solutions](#challenges-and-solutions)
   - [Design Challenges](#design-challenges)
   - [Coding Challenges](#coding-challenges)
5. [Future Work](#future-work)
6. [Acknowledgments](#acknowledgments)
7. [Appendices](#appendices)
   - [Datasheets and Specifications](#datasheets-and-specifications)
   - [References](#references)

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

## Functional Capabilities

### Obstacle Detection and Avoidance
The robot employs advanced algorithms to detect obstacles and execute avoidance maneuvers.

### Color Detection
Utilizes the HSV format for color detection, leveraging OpenCV’s capabilities to create masks for specific colors.

### Navigation and Movement
Features capabilities like lane following, acceleration/deceleration, and crash handling, ensuring smooth operation in dynamic environments.

## Challenges and Solutions

### Design Challenges
Discuss specific design challenges faced and how they were overcome.

### Coding Challenges
Highlight any coding difficulties encountered during development and their solutions.

## Future Work
Outline potential improvements and features for future iterations of the project.

## Acknowledgments
Thank those who contributed to the project, including mentors, team members, and supporters.

## Appendices

### Datasheets and Specifications
Provide links or references to datasheets for components used.

### References
Include references to any external resources or research papers relevant to the project.
