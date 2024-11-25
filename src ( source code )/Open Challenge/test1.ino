#include <Wire.h>
#include <Servo.h>

#define I2C_ADDRESS 0x08  // I2C address of this Arduino
#define switchPin  A0     // Switch pin

String receivedData = "";  // String to store the incoming message
bool receiving = false;    // Flag to check if we are in the middle of receiving a message
unsigned long lastReceiveTime = 0;  // Time when the last data was received
unsigned long timeoutDuration = 500;  // Timeout duration in milliseconds

// Motor control pins
#define ENA  11
#define IN_1 13
#define IN_2 12

#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo

Servo STEERING;  // Create Servo object for steering

// Motor control variables
int MaxSpeed = 255;
int MinSpeed = 127;
int steeringAngle = 0;

// Variables to store the parsed values
int FR, FL, L1, L2, R1, R2;

// Function to parse the received message
void parseMessage(String message) {
  if (message.startsWith("-") && message.endsWith(".")) {
    // Remove the start and end markers
    message = message.substring(1, message.length() - 1);

    // Split the message into individual parts
    int firstComma = message.indexOf(',');
    int secondComma = message.indexOf(',', firstComma + 1);
    int thirdComma = message.indexOf(',', secondComma + 1);
    int fourthComma = message.indexOf(',', thirdComma + 1);
    int fifthComma = message.indexOf(',', fourthComma + 1);

    // Parse each value
    FR = message.substring(0, firstComma).toInt();
    FL = message.substring(firstComma + 1, secondComma).toInt();
    L1 = message.substring(secondComma + 1, thirdComma).toInt();
    L2 = message.substring(thirdComma + 1, fourthComma).toInt();
    R1 = message.substring(fourthComma + 1, fifthComma).toInt();
    R2 = message.substring(fifthComma + 1).toInt();
  } else {
    // Invalid message format
    Serial.println("Error: Invalid message format");
  }
}


// Stop the motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);  // Stop motor by setting speed to 0
}

// Hold the motors in place
void HoldMotors() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, 0);  // Stop motor by setting speed to 0
}

// Check if the switch is on
bool isSwitchOn(int value) {
  return value > 1000;  // Return true if analog reading is close to 1023 (switch on)
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
      lastReceiveTime = millis();  // Update the last received time
    } else if (receiving) {
      // Append to the message if we're in the middle of receiving
      receivedData += c;
    }
  }
}

// Function to print the lidar output data in the serial monitor
void printLidarData() {
  // Check if data was recently received
  if (millis() - lastReceiveTime <= timeoutDuration) {
    if (receivedData.length() > 0) {
      Serial.println(receivedData);
    }
  } else {
    // Timeout occurred, print zeros
    Serial.println("0,0,0,0,0,0.");
  }
}

// Existing motor control function
void controlRobot(int speedInput, int steeringInput) {
  // Map speedInput from -100 to 100 to motor speed range
  int motorSpeed = map(abs(speedInput), 0, 100, MinSpeed, MaxSpeed);
  
  // Set motor direction based on the sign of speedInput
  if (speedInput > 0) {
    // Move forward
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  } else if (speedInput < 0) {
    // Move backward
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
  } else {
    // Stop motors
    StopMotors();
  }

  // Set motor speed
  analogWrite(ENA, motorSpeed);

  // Map steeringInput from -100 to 100 to servo angle range (120 to 60 degrees)
  steeringAngle = map(steeringInput, -100, 100, 120, 60);

  // Set servo position
  STEERING.write(steeringAngle);
}

// Robot action function (only for printing to Serial Monitor when switch is on)
void act() {
  printLidarData();
}

void setup() {
  Wire.begin(I2C_ADDRESS);  // Join the I2C bus with the specified address
  Wire.onReceive(receiveEvent);  // Register the receive event
  Serial.begin(9600);  // Start the Serial Monitor
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

  // Attach servo
  STEERING.attach(STEERING_SERVO_PIN);

  // Stop motors and set servo to neutral position
  StopMotors();
  controlRobot(0, 0);
}

void loop() {
  int switchValue = analogRead(switchPin);  // Read the analog value of the switch

  if (isSwitchOn(switchValue)) {  // Check if switch is on
    act();  // Perform robot actions when the switch is on
  } else {
    StopMotors();  // Stop motors when the switch is off
    controlRobot(0, 0);

  }

  delay(100);  // Short delay for stability
}
