#include <Wire.h>

#define I2C_ADDRESS 0x08  // I2C address of this Arduino

String receivedData = "";  // String to store the incoming message
bool receiving = false;    // Flag to check if we are in the middle of receiving a message

void setup() {
  Wire.begin(I2C_ADDRESS);  // Join the I2C bus with the specified address
  Wire.onReceive(receiveEvent);  // Register the receive event
  Serial.begin(9600);       // Start the Serial Monitor
}

void loop() {
  if (!receiving && receivedData.length() > 0) {  // Check if the String is not empty
    // If a complete message is received, print it to the Serial Monitor
    Serial.println("Received Full Message: " + receivedData);
    delay(1000);  // Wait for a while before clearing the message
    receivedData = "";  // Clear the buffer for the next message
  }
}

// Function to handle data received over I2C
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
