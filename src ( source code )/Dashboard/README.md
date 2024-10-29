# WRO Future Engineers Competition - Robot Dashboard

This project is a Tkinter-based dashboard designed to enhance the **WRO Future Engineers Competition** robot with a camera preview, HSV color tuning, sensor readings, and temperature monitoring. This documentation includes detailed explanations of each part of the code, along with usage and setup instructions.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Project Structure](#project-structure)
4. [Code Explanation](#code-explanation)
   - [Imports](#imports)
   - [Camera Configuration](#camera-configuration)
   - [HSV Color Tuning](#hsv-color-tuning)
   - [Dashboard Layout](#dashboard-layout)
   - [Temperature Monitoring](#temperature-monitoring)
   - [Run Dashboard](#run-dashboard)
5. [How to Run](#how-to-run)
6. [Usage](#usage)
7. [Acknowledgments](#acknowledgments)

---

## Introduction
The dashboard provides a real-time interface to monitor and adjust the robot’s camera, view LiDAR data, monitor temperatures, and control color detection. 

## Installation

### Step 1: Clone the Repository
```bash
git clone https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International
cd WRO-FE-2024-Mindcraft-International
```

### Step 2: Install Required Libraries
Install the required Python libraries using pip:

```bash
pip install tkinter pillow numpy opencv-python
```

### Step 3: Set Up the Raspberry Pi Camera
Enable the Raspberry Pi camera:

```bash
sudo raspi-config
```

Go to `Interface Options` > `Camera` and enable it.

## Project Structure
```plaintext
Dashboard/
├── README.md          # Project documentation file
└── Dashboard.py            # Main Python code file for the dashboard
```

## Code Explanation
### Imports
The initial code imports necessary libraries:

```python
import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import numpy as np
import cv2
```

__Tkinter__: Used for building the GUI.
__ttk__: Provides themed widgets.
__PIL__: For image handling in Tkinter.
__NumPy__: For efficient array handling.
__OpenCV__: Used for camera operations and color detection.

---

### Camera Configuration
The camera capture setup uses OpenCV to initialize and process the camera feed:

```python
cap = cv2.VideoCapture(0)  # 0 is typically the Pi camera
```
- `cap`: The camera object, which streams the video feed.
-This feed is displayed on the Tkinter GUI and processed for color detection.

### HSV Color Tuning
To detect specific colors, HSV values are adjusted through sliders:

```python
hue_min = tk.IntVar()
sat_min = tk.IntVar()
val_min = tk.IntVar()
# And similar variables for the upper HSV bounds
```

- HSV Sliders: The dashboard provides controls for setting `hue`, `saturation`, and `value` ranges for colors to detect.
- Mask Creation: A mask is created based on HSV values to isolate colors:
```python
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
mask = cv2.inRange(hsv, (hue_min.get(), sat_min.get(), val_min.get()),
                   (hue_max.get(), sat_max.get(), val_max.get()))
```

__Filtered Display__: The mask result is displayed in a dedicated area on the dashboard, allowing real-time HSV adjustments.

### Dashboard Layout
The GUI layout is set up to place each component strategically:
```python
root = tk.Tk()
root.geometry("800x480")
```
- __Main Window__: Configured for 800x480 resolution to fit the Raspberry Pi screen.
- __Frames and Widgets__:
- __Camera Preview__: Shows the live camera feed.
- __Map and LiDAR__: A placeholder to show the competition map and integrate LiDAR sensor data.
- __HSV Sliders__: Positioned beside the camera for easy color tuning.
  
### Temperature Monitoring
A helper function reads CPU and GPU temperatures:
```python
def get_cpu_temp():
    # Reads CPU temperature
```
- __Temperature Data__: Retrieved from system files to display in real-time on the dashboard.
---

### Run Dashboard
The main loop runs the dashboard, refreshing the frames:

```python
while True:
    ret, frame = cap.read()
    # Camera and mask display updates
    root.update_idletasks()
    root.update()
```
- __Frame Capture__: Updates the camera feed and applies the HSV mask.
- __Root Loop__: Keeps the Tkinter dashboard running, refreshing the interface.

---
### How to Run
1) Open a terminal in the project directory.
2) Run the following command:
```bash
python main.py
```
3) The Tkinter dashboard should open, displaying the camera feed, map, temperature, and HSV control panel.

---
## Usage
### Adjusting HSV Values
1) Use the sliders to adjust `hue`, `saturation`, and `value` ranges for detecting specific colors.
2) Observe changes in the masked feed to identify the target color range.
   
### Monitoring Sensor Data
- __Temperature__: View the CPU and GPU temperatures in real-time.

---
## Acknowledgments
- __OpenCV__ for image processing.
- __Pillow__ for handling image rendering in Tkinter.
- __NumPy__ for matrix operations.







