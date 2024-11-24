#include <Wire.h>
#include <Servo.h>

#define I2C_ADDRESS 0x08  // I2C address of this Arduino

// Define the switch pin
#define switchPin  A0  // Switch pin

String receivedData = "";  // String to store the incoming message
bool receiving = false;    // Flag to check if we are in the middle of receiving a message

// Buzzer functions (no longer used for now)
void BuzzerRobotError() {
  // You can keep this function for error indication if necessary
  for (int i = 0; i < 5; i++) {
    tone(8, 1500);  // Tone at 1500Hz (you can change the pin if needed)
    delay(100);
    noTone(8);  // Stop tone
    delay(100);
  }
}

// Check if the switch is on
bool isSwitchOn(int value) {
  return value > 1000;  // Return true if analog reading is close to 1023 (switch on)
}

// Function to handle data received over I2C (for future use, if necessary)
void receiveEvent(int bytesReceived) {
  while (Wire.available()) {
    char c = Wire.read();  // Read one byte from I2C
    if (c == '-') {
      // Start of a new message
      receivedData = "-";
      receiving = true;
    } else if (c == '.' && receiving) {
      // End of the message
      receivedData += ".";
      receiving = false;
    } else if (receiving) {
      // Append to the message if we're in the middle of receiving
      receivedData += c;
    }
  }
}

// Function to print the lidar output data in the serial monitor
void printLidarData() {
  // If you want to display the full received message from I2C
  if (receivedData.length() > 0) {
    Serial.println(receivedData);
  }
}
// Robot action function (only for printing to Serial Monitor when switch is on)
void act() {
  printLidarData();
}

void setup() {
  Wire.begin(I2C_ADDRESS);  // Join the I2C bus with the specified address
  Wire.onReceive(receiveEvent);  // Register the receive event
  Serial.begin(9600);       // Start the Serial Monitor
}

void loop() {
  int switchValue = analogRead(switchPin);  // Read the analog value of the switch

  if (isSwitchOn(switchValue)) {  // Check if switch is on
    act();  // Print to Serial Monitor when the switch is on
  } else {
    // If switch is off, optionally handle error or stop motors
    BuzzerRobotError();  // Error sound when switch is off
  }

  delay(100);  // Short delay for stability
}
