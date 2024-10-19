import serial
import time

# Initialize serial communication
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Update with your actual port
time.sleep(2)  # Allow time for the Arduino to reset

try:
    while True:
        # Turn ON the buzzer
        ser.write(b'1')  
        print("Buzzer ON")
        time.sleep(2)  # Keep the buzzer on for 2 seconds
        
        # Turn OFF the buzzer
        ser.write(b'0')  
        print("Buzzer OFF")
        time.sleep(2)  # Keep the buzzer off for 2 seconds

except KeyboardInterrupt:
    # Stop the loop if interrupted (Ctrl + C)
    print("Stopping buzzer control...")

finally:
    # Close the serial connection when done
    ser.close()
    print("Serial connection closed.")
