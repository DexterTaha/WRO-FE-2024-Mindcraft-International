from picamera2 import Picamera2
import cv2
import numpy as np

# Initialize Picamera2 with camera index 0
picam2 = Picamera2(camera_num=0)

# Create a preview configuration
config = picam2.create_preview_configuration()
picam2.configure(config)

# Start the camera
picam2.start()

# Create a window to display the results
cv2.namedWindow("Color Detection Dashboard")

# Create trackbars for HSV color detection
def nothing(x):
    pass

# Create sliders for green color
cv2.createTrackbar("H Min (Green)", "Color Detection Dashboard", 30, 179, nothing)
cv2.createTrackbar("H Max (Green)", "Color Detection Dashboard", 90, 179, nothing)
cv2.createTrackbar("S Min (Green)", "Color Detection Dashboard", 100, 255, nothing)
cv2.createTrackbar("S Max (Green)", "Color Detection Dashboard", 255, 255, nothing)
cv2.createTrackbar("V Min (Green)", "Color Detection Dashboard", 100, 255, nothing)
cv2.createTrackbar("V Max (Green)", "Color Detection Dashboard", 255, 255, nothing)

# Create sliders for red color
# Create sliders for red color (adjusted for hue wrapping)
cv2.createTrackbar("H Min (Red)", "Color Detection Dashboard", 0, 179, nothing)
cv2.createTrackbar("H Max (Red)", "Color Detection Dashboard", 10, 179, nothing)
cv2.createTrackbar("S Min (Red)", "Color Detection Dashboard", 100, 255, nothing)
cv2.createTrackbar("S Max (Red)", "Color Detection Dashboard", 255, 255, nothing)
cv2.createTrackbar("V Min (Red)", "Color Detection Dashboard", 100, 255, nothing)
cv2.createTrackbar("V Max (Red)", "Color Detection Dashboard", 255, 255, nothing)

# Add an additional range for the upper red hue
cv2.createTrackbar("H Min (Red 2)", "Color Detection Dashboard", 160, 179, nothing)
cv2.createTrackbar("H Max (Red 2)", "Color Detection Dashboard", 180, 179, nothing)


while True:
    # Capture frame
    frame = picam2.capture_array()

    # Invert the camera frame (flip vertically)
    frame = cv2.flip(frame, 0)  # 0 indicates vertical flip

    # Convert the frame to HSV
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Get the current values from the trackbars for green
    h_min_g = cv2.getTrackbarPos("H Min (Green)", "Color Detection Dashboard")
    h_max_g = cv2.getTrackbarPos("H Max (Green)", "Color Detection Dashboard")
    s_min_g = cv2.getTrackbarPos("S Min (Green)", "Color Detection Dashboard")
    s_max_g = cv2.getTrackbarPos("S Max (Green)", "Color Detection Dashboard")
    v_min_g = cv2.getTrackbarPos("V Min (Green)", "Color Detection Dashboard")
    v_max_g = cv2.getTrackbarPos("V Max (Green)", "Color Detection Dashboard")

    # Get the current values from the trackbars for red
    h_min_r = cv2.getTrackbarPos("H Min (Red)", "Color Detection Dashboard")
    h_max_r = cv2.getTrackbarPos("H Max (Red)", "Color Detection Dashboard")
    s_min_r = cv2.getTrackbarPos("S Min (Red)", "Color Detection Dashboard")
    s_max_r = cv2.getTrackbarPos("S Max (Red)", "Color Detection Dashboard")
    v_min_r = cv2.getTrackbarPos("V Min (Red)", "Color Detection Dashboard")
    v_max_r = cv2.getTrackbarPos("V Max (Red)", "Color Detection Dashboard")

    # Define the lower and upper bounds for green and red
    lower_green = np.array([h_min_g, s_min_g, v_min_g])
    upper_green = np.array([h_max_g, s_max_g, v_max_g])
    
    lower_red1 = np.array([h_min_r, s_min_r, v_min_r])
    upper_red1 = np.array([h_max_r, s_max_r, v_max_r])
    

    
    lower_red2 = np.array([160, s_min_r, v_min_r])  # Adjust for red hue wrap
    upper_red2 = np.array([h_max_r, s_max_r, v_max_r])
    
            # Get the current values from the trackbars for the second red range
    h_min_r2 = cv2.getTrackbarPos("H Min (Red 2)", "Color Detection Dashboard")
    h_max_r2 = cv2.getTrackbarPos("H Max (Red 2)", "Color Detection Dashboard")

    lower_red2 = np.array([h_min_r2, s_min_r, v_min_r])  # Using values from the sliders
    upper_red2 = np.array([h_max_r2, s_max_r, v_max_r])


    # Threshold the HSV image to get only the desired colors
    mask_green = cv2.inRange(hsv_frame, lower_green, upper_green)
    mask_red1 = cv2.inRange(hsv_frame, lower_red1, upper_red1)
    mask_red2 = cv2.inRange(hsv_frame, lower_red2, upper_red2)

    # Combine the masks for red
    mask_red = cv2.bitwise_or(mask_red1, mask_red2)

    # Combine masks for green and red
    mask_combined = cv2.bitwise_or(mask_green, mask_red)

    # Find contours in the masks
    contours, _ = cv2.findContours(mask_combined, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Draw rectangles around detected colors
    for contour in contours:
        if cv2.contourArea(contour) > 100:  # Filter small contours
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)  # Green rectangle

    # Create a mask frame
    mask_display = cv2.cvtColor(mask_combined, cv2.COLOR_GRAY2BGR)

    # Add text labels for detected colors
    cv2.putText(frame, "Green", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.putText(frame, "Red", (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Ensure the frame is three channels for concatenation
    if frame.shape[2] == 4:  # If there are four channels
        frame = frame[:, :, :3]  # Convert to three channels by dropping the alpha channel

    # Combine the original frame and mask for display
    combined_display = np.hstack((frame, mask_display))

    # Show the resulting frame
    cv2.imshow("Color Detection Dashboard", combined_display)

    # Exit the loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Cleanup
picam2.stop()
cv2.destroyAllWindows()

