#include <Servo.h>        // Include the Servo library
#include <Wire.h>         // Include the Wire library for I2C communication

#define I2C_ADDRESS 0x08  // I2C address of this Arduino

// Define motors and sensor pins
#define ENA  11                // L298N EN_A motor speed
#define IN_1  13               // L298N in1 motor direction control
#define IN_2  12               // L298N in2 motor direction control
#define buzzerPin  8           // Pin for the buzzer
#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo
#define switchPin  A0          // Switch pin

Servo STEERING;  // Create Servo object for steering

// Motor control variables
int MaxSpeed = 255;
int MinSpeed = 127;
int steeringAngle = 90;  // Default steering angle (centered)

String receivedData = "";  // String to store the incoming message
bool receiving = false;    // Flag to check if we are in the middle of receiving a message

// Direction control variables
int ccw = 0; // Counter-clockwise
int cw = 1;  // Clockwise

// Function to drive the robot
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

  // Map steeringInput from -100 to 100 to servo angle range (130 to 50 degrees)
  steeringAngle = map(steeringInput, -100, 100, 120, 60);

  // Set servo position
  STEERING.write(steeringAngle);
}

// Motor control function for CW
void controlRobotCW(int rightDistance, int backRightDistance) {
  int targetDistance = 30;  // Target wall distance (cm)
  int averageRight = (rightDistance + backRightDistance) / 2;

  // Adjust steering based on the distance
  if (abs(averageRight - targetDistance) > 2) {
    int adjustment = (averageRight > targetDistance) ? -5 : 5;
    steeringAngle = constrain(steeringAngle + adjustment, 60, 120);
    STEERING.write(steeringAngle);
  }

  // Drive forward
  controlRobot(50, 0);  // Speed: 50%, Steering: Centered
}

// Stop motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
}

// Hold motors (keep them idle)
void HoldMotors() {
  StopMotors();
}

// Buzzer functions
void BuzzerRobotStart() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotEnd() {
  tone(buzzerPin, 500);
  delay(1000);
  noTone(buzzerPin);
}

void BuzzerRobotError() {
  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  }
}

// Check if the switch is on
bool isSwitchOn(int value) {
  return value > 1000;  // Return true if analog reading is close to 1023 (switch on)
}

// Robot action function
void act() {
  sendDataToPi();       // Send sensor and motor data to Raspberry Pi
  receiveDataFromPi();  // Receive control data from Raspberry Pi
}

// Send data to Raspberry Pi
void sendDataToPi() {
  // Placeholder function for sending data to Raspberry Pi
}

// Process received data from Raspberry Pi
void receiveDataFromPi() {
  if (!receiving && receivedData.length() > 0) {
    Serial.println("Received Full Message: " + receivedData);
    int distances[6];
    sscanf(receivedData.c_str(), "-%d,%d,%d,%d,%d,%d.", &distances[0], &distances[1], &distances[2], &distances[3], &distances[4], &distances[5]);

    if (cw == 1 && ccw == 0) {
      controlRobotCW(distances[4], distances[5]);  // Use right-side sensors for CW
    } else {
      StopMotors();  // Default behavior if invalid configuration
      BuzzerRobotError();
    }

    receivedData = "";
  }
}

// Handle data received over I2C
void receiveEvent(int bytesReceived) {
  while (Wire.available()) {
    char c = Wire.read();
    if (c == '-') {
      receivedData = "-";
      receiving = true;
    } else if (c == '.' && receiving) {
      receivedData += ".";
      receiving = false;
    } else if (receiving) {
      receivedData += c;
    }
  }
}

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  STEERING.attach(STEERING_SERVO_PIN);

  StopMotors();
  BuzzerRobotStart();
}

// Loop function
void loop() {
  int switchValue = analogRead(switchPin);  // Read the analog value of the switch

  if (isSwitchOn(switchValue)) {  // Check if switch is on
    act();
  } else {
    HoldMotors();
    BuzzerRobotError();
  }
}
