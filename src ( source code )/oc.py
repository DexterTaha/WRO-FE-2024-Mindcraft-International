from picamera2 import Picamera2
import cv2
import numpy as np
import serial
import time

# Initialize Serial Communication
try:
    arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
    time.sleep(2)  # Wait for Arduino to initialize
except serial.SerialException:
    print("Could not open serial port. Check your connection.")
    exit()

# Camera Initialization
def initialize_camera():
    picam2 = Picamera2()
    config = picam2.create_preview_configuration(main={"size": (640, 480)})
    picam2.configure(config)
    picam2.start()
    return picam2

# Send Control Commands to Arduino
def send_control_commands(speed, steering):
    if arduino.is_open:
        control_string = f"{speed},{steering}\n"
        arduino.write(control_string.encode())
        print(f"Sent command: Speed={speed}, Steering={steering}")

# Receive and Parse Sensor Data from Arduino
def receive_sensor_data():
    if arduino.in_waiting > 0:
        data = arduino.readline().decode().strip()
        print(f"Received raw data: {data}")  # Debugging: Print the raw data received
        try:
            values = data.split(',')
            if len(values) == 6:  # Ensure we have exactly 6 values
                front, right, left, back, gyro = map(int, values[:5])  # First five values as integers
                rpm = float(values[5])  # Last value as a float
                return {
                    "front": front,
                    "right": right,
                    "left": left,
                    "back": back,
                    "gyro": gyro,
                    "rpm": rpm
                }
            else:
                print("Unexpected data format or missing values")
        except ValueError:
            print("Failed to parse sensor data due to value error.")
    return None


# PID Controller Class for Steering Adjustments
class PID:
    def __init__(self, kp, ki, kd, min_output=-100, max_output=100):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.previous_error = 0
        self.integral = 0
        self.min_output = min_output
        self.max_output = max_output

    def compute(self, setpoint, measured_value):
        error = setpoint - measured_value
        self.integral += error
        derivative = error - self.previous_error
        output = (self.kp * error) + (self.ki * self.integral) + (self.kd * derivative)
        output = max(self.min_output, min(self.max_output, output))
        self.previous_error = error
        return output

# Color Detection and Processing for Navigation
def color_detection(img, hsv_ranges):
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    masks = [cv2.inRange(hsv, lower, upper) for (lower, upper) in hsv_ranges]
    return masks

# Mission-Specific Function for Obstacle Avoidance and Navigation
def navigate_mission(sensor_data, pid_controller, target_position=0):
    if sensor_data:
        front_distance = sensor_data["front"]
        error = target_position - front_distance
        steering_output = pid_controller.compute(0, error)
        # Send control commands with a speed level suited for navigation
        send_control_commands(speed=30, steering=steering_output)

# Main Execution Loop
def main():
    speed_percentage = 50  # Base speed, adjustable between 0 to 100%
    picam2 = initialize_camera()
    pid_controller = PID(kp=2.0, ki=0.0, kd=1.0)

    try:
        while True:
            # Capture Frame from Camera
            frame = picam2.capture_array()
            frame = cv2.resize(frame, (640, 480))

            # Color Detection (assuming red, green, and black masks for walls or lanes)
            hsv_ranges = [
                ((97, 170, 70), (180, 255, 255)),  # Red
                ((27, 155, 3), (75, 255, 255)),    # Green
                ((0, 0, 0), (180, 255, 50))        # Black
            ]
            masks = color_detection(frame, hsv_ranges)
            red_mask, green_mask, black_mask = masks

            # Process and Display Detected Colors for Debugging
            cv2.imshow("Red Mask", red_mask)
            cv2.imshow("Green Mask", green_mask)
            cv2.imshow("Black Mask", black_mask)

            # Receive Sensor Data from Arduino
            sensor_data = receive_sensor_data()

            # Mission Execution Logic (e.g., wall following or obstacle avoidance)
            if sensor_data:
                # Example Mission: Wall Following with PID-based Steering
                navigate_mission(sensor_data, pid_controller, target_position=100)  # Target position in cm from wall

            # Exit on 'q' key press
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    finally:
        picam2.stop()
        cv2.destroyAllWindows()
        arduino.close()

if __name__ == "__main__":
    main()
