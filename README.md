MINDCRAFT WRO Future Engineers team
====

<p align="center">
  <img src="https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/1b560d62026fe432f3dff80fa5efd213787d7d30/images/team.png" alt="banner" width="1500">
</p>


This repository provides information and knowledge regarding the ongoing progress, evolution, and development of our self-driving robot vehicle, which was created and coded by us, [Salmane Derdeb](https://github.com/salmane-derdeb),  [Taha TAIDI LAAMIRI](https://github.com/DexterTaha) and [Mortada TAIDI LAAMIRI]() as participants in the Future Engineers 2024 division of the World Robot Olympiad (WRO).

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


# WRO Future-Engineers Competition:

## Table of Contents

- **[Project Overview](#project-overview)**  
   - [Competition Context](#competition-context)  
   - [Team Management](#team-management)  
   - [Vehicle Strengths and Limitations](#vehicle-strengths-and-limitations)  

- **[Technical Overview](#technical-overview)**  
   - **Hardware Design**  
      - [Chassis](#chassis)  
      - [Power and Control](#power-and-control)  
      - [Sensors](#sensors)  
      - [Wiring Diagram](#wiring-diagram)  
   - **Software Design**  
      - [Programming Languages & Libraries](#programming-languages-libraries)  
      - [Algorithms](#algorithms)  

- **[Programming and Algorithms](#programming-and-algorithms)**  
   - [Detecting Turns & Direction](#detecting-turns-direction)  
   - [Lap Counting](#lap-counting)  
   - [IMU-Based Steering](#imu-based-steering)  
   - [PID Controller](#pid-controller)  
   - [Turn Execution](#turn-execution)  

- **[Challenges](#challenges)**  
   - **Obstacle Avoidance Round**  
      - [Obstacle Challenge Overview](#obstacle-challenge-overview)  
      - [Pillar Detection](#pillar-detection)  
      - [Obstacle Avoidance Strategy](#obstacle-avoidance-strategy)  
   - **Design Challenges**  
      - [Hardware Challenges](#hardware-challenges)  
      - [Sensor & Coding Challenges](#sensor-coding-challenges)  
      - [Mechanical Challenges](#mechanical-challenges)  

- **[Future Work and Reflections](#future-work-and-reflections)**  
   - [Future Work](#future-work)  
   - [Reflections and Gratitude](#reflections-and-gratitude)  

- **[Acknowledgments](#acknowledgments)**  

- **[Appendices](#appendices)**  
   - [Datasheets & Specifications](#datasheets-specifications)  
   - [References](#references)  

- **[Demonstrations](#demonstrations)**  
   - [Demonstration Videos](#demonstration-videos)  
   - [Photos](#photos)  
   - [Team Photos](#team-photos)  

- **[Lessons Learned](#lessons-learned)**  

- **[Safety Notes](#safety-notes)**  
   - [LiPo Battery Safety](#lipo-battery-safety)

## Project Overview

### Aim and Objectives
The primary aim of this robot project is to develop an autonomous vehicle capable of navigating its environment effectively. The key objectives include:

1. Detecting and avoiding obstacles in real-time.
2. Implementing autonomous driving capabilities.
3. Enabling state detection and automatic correction in case of errors.
4. Performing tasks efficiently within competition constraints.

### Competition Context:
The WRO Future Engineers 2024 competition challenges teams to design, build, and program advanced autonomous robots to solve real-world engineering problems. Robots must navigate complex environments, interact with objects, and perform tasks using sophisticated sensors such as LiDAR, DTOF, and gyroscopes. The emphasis is on both the technical aspects, like precision and programming (often using platforms like Jetson Nano or Raspberry Pi), and the engineering design, focusing on efficient mechanical systems. Teams will be evaluated based on their robot's performance, problem-solving, and ability to innovate, with a focus on themes like automation and sustainability.
