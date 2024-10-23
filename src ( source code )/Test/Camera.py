from picamera2 import Picamera2
import cv2
import numpy as np

# Initialize Picamera2
picam2 = Picamera2(camera_num=0)
config = picam2.create_preview_configuration()
picam2.configure(config)
picam2.start()

# Define your color range for red detection
lower_red = np.array([97, 170, 70])   # Adjust these values for red
upper_red = np.array([180, 255, 255])  # Adjust these values for red
#lower_red = np.array([113, 70, 32])   # Adjust these values for red
#upper_red = np.array([154, 255, 160])  # Adjust these values for red

# Define your color range for green detection
#lower_green = np.array([25, 250, 40])   # Adjust these values for green
#upper_green = np.array([77, 255, 255])    # Adjust these values for green
lower_green = np.array([27, 155, 3])   # Adjust these values for green
upper_green = np.array([75, 255, 255])    # Adjust these values for green

while True:
    # Capture frame
    frame = picam2.capture_array()
    frame = cv2.resize(frame, (640, 480))

    # Flip the frame vertically
    frame = cv2.flip(frame, 0)

    # Convert the frame to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create masks for red and green detection
    mask_red = cv2.inRange(hsv, lower_red, upper_red)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    # Combine the masks
    mask_combined = cv2.bitwise_or(mask_red, mask_green)

    # Apply a binary threshold to the combined mask
    _, mask1 = cv2.threshold(mask_combined, 254, 255, cv2.THRESH_BINARY)

    # Find contours in the thresholded mask
    cnts, _ = cv2.findContours(mask1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    # Draw rectangles around detected contours and print detected color
    for c in cnts:
        area_threshold = 600
        if cv2.contourArea(c) > area_threshold:
            x, y, w, h = cv2.boundingRect(c)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Check which color was detected
            if cv2.countNonZero(mask_red[y:y+h, x:x+w]) > 0:
                detected_color = "RED"
            elif cv2.countNonZero(mask_green[y:y+h, x:x+w]) > 0:
                detected_color = "GREEN"
            else:
                detected_color = "UNKNOWN"

            # Display the detected color on the frame
            cv2.putText(frame, detected_color, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
            print("Detected color:", detected_color)

    # Show the resulting frame
    cv2.imshow("FRAME", frame)

    # Exit the loop when 'ESC' is pressed
    if cv2.waitKey(1) & 0xFF == 27:
        break

# Cleanup
picam2.stop()
cv2.destroyAllWindows()
