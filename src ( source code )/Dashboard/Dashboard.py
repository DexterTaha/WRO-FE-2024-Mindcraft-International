import tkinter as tk
import os
from tkinter import *
from PIL import ImageTk, Image
import numpy as np
import cv2
from picamera2 import Picamera2  # Import Picamera2

Image.MAX_IMAGE_PIXELS = None

# Function to create and place borders with curved appearance
def add_rounded_border(frame, radius=10):
    frame.config(highlightbackground="black", highlightthickness=2)

# Initialize the main window
root = tk.Tk()
root.title("Robot Dashboard")
root.geometry("840x540")  # Adjusted window size

# Frame for the main grid layout
main_frame = tk.Frame(root, bg="#f0f0f0")  # Light background color
main_frame.grid(row=0, column=0, sticky="nsew")
main_frame.grid_rowconfigure(0, weight=1)
main_frame.grid_columnconfigure(0, weight=1)

# --- Camera Preview ---

camera_frame = tk.Frame(main_frame, width=266, height=60, bg="white", bd=2, relief="flat")
camera_frame.grid(row=0, column=0, columnspan=2, padx=2, pady=2, sticky="nsew")
camera_label = tk.Label(camera_frame, text="Camera Preview", font=("Helvetica", 12), bg="white")
camera_label.pack(pady=3)

camera_canvas = tk.Canvas(camera_frame, width=233, height=120, bg="#cccccc")  # Grey background
camera_canvas.pack(pady=2)

# Initialize Picamera2
picam2 = Picamera2()
picam2.configure(picam2.create_preview_configuration())
picam2.start()


# --- LiDAR Preview ---
lidar_frame = tk.Frame(main_frame, width=266, height=100, bg="white", bd=2, relief="flat")
lidar_frame.grid(row=1, column=0, columnspan=2, padx=2, pady=2, sticky="nsew")
lidar_label = tk.Label(lidar_frame, text="LiDAR Scanning", font=("Helvetica", 12), bg="white")
lidar_label.pack(pady=2)
lidar_canvas = tk.Canvas(lidar_frame, width=233, height=70, bg="#cccccc")
lidar_canvas.pack(pady=2)

# --- Map with Image ---
map_frame = tk.Frame(main_frame, width=266, height=100, bg="white", bd=2, relief="flat")
map_frame.grid(row=2, column=0, columnspan=2, padx=2, pady=2, sticky="nsew")

# Load the map image with Pillow
map_image = Image.open("/home/mindcraft/Desktop/img/WRO-2024_FutureEngineers_Playfield_page-0001-min.jpg")  # Update with your image path

# Desired width for resizing
desired_width = 246
# Calculate height to maintain aspect ratio
aspect_ratio = map_image.height / map_image.width
new_height = int(desired_width * aspect_ratio)

# Resize the image
map_image = map_image.resize((desired_width, new_height), Image.ANTIALIAS)
map_image = ImageTk.PhotoImage(map_image)

# Create a label to display the image
map_image_label = tk.Label(map_frame, image=map_image, bg="white")
map_image_label.pack(pady=2)

# Keep a reference to the image to prevent it from being garbage collected
map_image_label.image = map_image

# --- Variables (P1 to P24) ---
variables_frame = tk.Frame(main_frame, width=100, height=400, bg="white", bd=2, relief="flat")
variables_frame.grid(row=0, column=2, rowspan=3, padx=2, pady=2, sticky="nsew")
variables_label = tk.Label(variables_frame, text="Variables", font=("Helvetica", 12), bg="white")
variables_label.pack(pady=2)
for i in range(1, 25):
    tk.Label(variables_frame, text=f'P{i} = {i % 3}', font=("Helvetica", 10), bg="white").pack(anchor='w')

# --- Camera Control (HSV Tweak) ---
camera_control_frame = tk.Frame(main_frame, width=167, height=400, bg="white", bd=2, relief="flat")
camera_control_frame.grid(row=0, column=3, rowspan=3, padx=2, pady=2, sticky="nsew")
camera_control_label = tk.Label(camera_control_frame, text="Camera Control (HSV)", font=("Helvetica", 12), bg="white")
camera_control_label.pack(pady=2)

# Red HSV Controls
"""tk.Label(camera_control_frame, text="Red Lower:", font=("Helvetica", 10), bg="white").pack(anchor='w')
for param in ["Hue", "Saturation", "Value"]:
    tk.Label(camera_control_frame, text=param + ":", font=("Helvetica", 9), bg="white").pack(anchor='w')
    tk.Scale(camera_control_frame, from_=0, to=255, orient='horizontal', bg="white", troughcolor="red", length=133).pack(anchor='w')  # Set the length here

# Green HSV Controls
tk.Label(camera_control_frame, text="Green Lower:", font=("Helvetica", 10), bg="white").pack(anchor='w')
for param in ["Hue", "Saturation", "Value"]:
    tk.Label(camera_control_frame, text=param + ":", font=("Helvetica", 9), bg="white").pack(anchor='w')
    tk.Scale(camera_control_frame, from_=0, to=255, orient='horizontal', bg="white", troughcolor="green", length=133).pack(anchor='w')  # Set the length here
"""

# --- Mask Display and Control ---

camera_control_frame = tk.Frame(main_frame, width=167, height=400, bg="white", bd=2, relief="flat")
camera_control_frame.grid(row=0, column=3, rowspan=3, padx=2, pady=2, sticky="nsew")
camera_control_label = tk.Label(camera_control_frame, text="Camera Control (HSV)", font=("Helvetica", 12), bg="white")
camera_control_label.pack(pady=2)

# Create a canvas for mask display
mask_canvas = Canvas(camera_control_frame, width=170, height=100)
mask_canvas.pack()

# Create sliders for HSV values
l_h = Scale(camera_control_frame, from_=0, to=179, orient=HORIZONTAL, label="L - H", length=165)
l_h.pack()
l_s = Scale(camera_control_frame, from_=0, to=255, orient=HORIZONTAL, label="L - S", length=165)
l_s.pack()
l_v = Scale(camera_control_frame, from_=0, to=255, orient=HORIZONTAL, label="L - V", length=165)
l_v.pack()
u_h = Scale(camera_control_frame, from_=0, to=179, orient=HORIZONTAL, label="U - H", length=165)
u_h.set(179)
u_h.pack()
u_s = Scale(camera_control_frame, from_=0, to=255, orient=HORIZONTAL, label="U - S", length=165)
u_s.set(255)
u_s.pack()
u_v = Scale(camera_control_frame, from_=0, to=255, orient=HORIZONTAL, label="U - V", length=165)
u_v.set(255)
u_v.pack()

# Function to update the camera feed and mask simultaneously
def process_frame():
    # Capture frame from the camera once
    frame = picam2.capture_array()
    frame = cv2.flip(frame, 0)  # Flip vertically
    frame = cv2.flip(frame, 1)  # Flip horizontally
    
    # --- Camera Preview ---
    preview_frame = cv2.resize(frame, (233, 120))  # Resize for the preview canvas
    img = Image.fromarray(preview_frame)  # Convert to PIL Image
    img_tk = ImageTk.PhotoImage(img)  # Convert to ImageTk
    
    # Clear and update the camera canvas
    camera_canvas.delete("all")
    camera_canvas.create_image(0, 0, anchor='nw', image=img_tk)
    camera_canvas.image = img_tk  # Keep reference
    
    # --- Mask Processing ---
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # Get the HSV range from the sliders
    lower_hsv = np.array([l_h.get(), l_s.get(), l_v.get()])
    upper_hsv = np.array([u_h.get(), u_s.get(), u_v.get()])
    
    # Apply mask
    mask = cv2.inRange(hsv, lower_hsv, upper_hsv)
    
    # Use bitwise AND to get the result
    result = cv2.bitwise_and(frame, frame, mask=mask)
    
    # Convert the result to RGB format for Tkinter
    mask_image = cv2.cvtColor(result, cv2.COLOR_BGR2RGB)
    mask_image = cv2.resize(mask_image, (170, 100))  # Resize for mask canvas
    mask_pil = Image.fromarray(mask_image)
    mask_tk = ImageTk.PhotoImage(mask_pil)

    # Clear and update the mask canvas
    mask_canvas.delete("all")
    mask_canvas.create_image(0, 0, anchor=NW, image=mask_tk)
    mask_canvas.image = mask_tk  # Keep reference

    # Schedule the next frame
    root.after(10, process_frame)

# Start the camera and mask processing
process_frame()


# --- Gyro Graph Placeholder ---
gyro_frame = tk.Frame(main_frame, width=100, height=80, bg="white", bd=2, relief="flat")
gyro_frame.grid(row=0, column=4, padx=2, pady=2, sticky="nsew")
gyro_label = tk.Label(gyro_frame, text="Gyro Graph", font=("Helvetica", 12), bg="white")
gyro_label.pack(pady=2)
gyro_canvas = tk.Canvas(gyro_frame, width=100, height=70, bg="#cccccc")
gyro_canvas.pack(pady=2)

# --- Speed Graph Placeholder ---
speed_frame = tk.Frame(main_frame, width=100, height=100, bg="white", bd=2, relief="flat")
speed_frame.grid(row=1, column=4, padx=2, pady=2, sticky="nsew")
speed_label = tk.Label(speed_frame, text="Speed Graph", font=("Helvetica", 12), bg="white")
speed_label.pack(pady=2)
speed_canvas = tk.Canvas(speed_frame, width=200, height=70, bg="#cccccc")
speed_canvas.pack(pady=2)

main_frame.grid_columnconfigure(1, weight=4)  # Allow the speed frame to expand
# --- Car with Sensors ---
car_frame = tk.Frame(main_frame, width=100, height=100, bg="white", bd=2, relief="flat")
car_frame.grid(row=2, column=4, padx=2, pady=2, sticky="nsew")
car_label = tk.Label(car_frame, text="Car with Sensors", font=("Helvetica", 12), bg="white")
car_label.pack(pady=2)
car_canvas = tk.Canvas(car_frame, width=100, height=100, bg="#cccccc")
car_canvas.create_rectangle(20, 20, 73, 73, outline="black", width=1)
car_canvas.create_text(50, 15, text="Front: 20", font=("Helvetica", 8))
car_canvas.create_text(50, 85, text="Back: 30", font=("Helvetica", 8))  # Back sensor added
car_canvas.create_text(15, 50, text="Left: 10", font=("Helvetica", 8), angle=90)
car_canvas.create_text(85, 50, text="Right: 15", font=("Helvetica", 8), angle=270)
car_canvas.pack(pady=2)

# --- Control Panel ---
control_frame = tk.Frame(main_frame, width=100, height=100, bg="white", bd=2, relief="flat")
control_frame.grid(row=2, column=5, padx=2, pady=2, sticky="nsew")
control_label = tk.Label(control_frame, text="Control Panel", font=("Helvetica", 10), bg="white")
control_label.pack(pady=2)

# Functions to get CPU and GPU temperature
def get_cpu_temperature():
    """Reads the CPU temperature from the system file."""
    try:
        with open("/sys/class/thermal/thermal_zone0/temp", "r") as file:
            cpu_temp = float(file.read()) / 1000.0  # Convert from millidegrees to Celsius
        return cpu_temp
    except FileNotFoundError:
        return None

def get_gpu_temperature():
    """Uses the vcgencmd command to get the GPU temperature."""
    gpu_temp = os.popen("vcgencmd measure_temp").readline()
    if gpu_temp:
        gpu_temp = gpu_temp.replace("temp=", "").replace("'C\n", "")  # Clean up the string
        return float(gpu_temp)
    return None

# Function to update temperature labels
def update_temperatures():
    cpu_temp = get_cpu_temperature()
    gpu_temp = get_gpu_temperature()
    
    # Update labels with current temperature values
    if cpu_temp is not None:
        cpu_label.config(text=f"CPU Temperature: {cpu_temp:.1f}")
    else:
        cpu_label.config(text="CPU Temperature: N/A")
    
    if gpu_temp is not None:
        gpu_label.config(text=f"GPU Temperature: {gpu_temp:.1f}")
    else:
        gpu_label.config(text="GPU Temperature: N/A")
    
    # Call the update function again after 1000 ms (1 second)
    control_frame.after(1000, update_temperatures)


# CPU/GPU temperature display
tk.Label(control_frame, text="Temp CPU:", font=("Helvetica", 8), bg="white").pack(anchor='w')
cpu_label = tk.Label(control_frame, text="--", font=("Helvetica", 8), bg="white")
cpu_label.pack(anchor='w')

tk.Label(control_frame, text="Temp GPU:", font=("Helvetica", 8), bg="white").pack(anchor='w')
gpu_label=tk.Label(control_frame, text="--", font=("Helvetica", 8), bg="white")
gpu_label.pack(anchor='w')

update_temperatures()

# Buttons for camera control
buttons = [
    ("Switch 1", 6),
    ("Switch 2", 6),
    ("Start Record", 6),
    ("Pause", 6),
    ("Stop Record", 6)
]


for btn_text, padding in buttons:
    tk.Button(control_frame, text=btn_text, font=("Helvetica", 8), relief="flat", bg="#e0e0e0", bd=1).pack(pady=padding)




# --- Placeholder for Logo (on the right side) ---
logo_frame = tk.Frame(main_frame, width=100, height=67, bg="white")
logo_frame.grid(row=0, column=5, rowspan=2, padx=2, pady=2, sticky="nsew")

# Load and rotate the logo image
logo_image = Image.open("/home/mindcraft/Desktop/img/banner.png")  # Update with your logo image path
logo_image = logo_image.rotate(90, expand=True)  # Rotate 90 degrees and expand to fit

# Resize the logo while maintaining the aspect ratio
aspect_ratio = logo_image.height / logo_image.width
new_width = 53  # Set the new width
new_height = int(new_width * aspect_ratio)  # Calculate height to maintain aspect ratio
logo_image = logo_image.resize((new_width, new_height), Image.ANTIALIAS)

logo_image = ImageTk.PhotoImage(logo_image)

# Create a label to display the rotated logo image without borders
logo_image_label = tk.Label(logo_frame, image=logo_image, bg="white", borderwidth=0)
logo_image_label.pack(pady=2)

# Keep a reference to the logo image to prevent it from being garbage collected
logo_image_label.image = logo_image


# Run the main loop
root.mainloop()

