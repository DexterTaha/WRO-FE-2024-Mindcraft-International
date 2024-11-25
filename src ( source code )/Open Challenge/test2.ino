#include <Wire.h>
#include <Servo.h>

#define I2C_ADDRESS 0x08  // I2C address of this Arduino
#define SWITCH_PIN A0     // Switch pin

String receivedData = "";          // String to store the incoming message
bool receiving = false;            // Flag to check if we are in the middle of receiving a message
unsigned long lastReceiveTime = 0; // Time when the last data was received
unsigned long timeoutDuration = 500; // Timeout duration in milliseconds

// Motor control pins
#define ENA  11
#define IN_1 13
#define IN_2 12
#define buzzerPin  8           // Pin for the buzzer
#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo

Servo STEERING;                // Create Servo object for steering

// Motor control variables
int maxSpeed = 255;
int minSpeed = 127;
int steeringAngle = 0;

// Variables to store the parsed values
int FR = 0, FL = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;

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

// Existing buzzer functions
void BuzzerRobotStart() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);  // Frequency of 1000 Hz
    delay(200);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotEnd() {
  tone(buzzerPin, 500);  // Lower frequency for end sound
  delay(1000);           // Long beep for 1 second
  noTone(buzzerPin);
}

void BuzzerRobotError() {
  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1500);  // Higher frequency for error
    delay(100);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotSpecial() {
  int melody[] = { 262, 294, 330, 349 };  // Notes for C, D, E, F
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, melody[i]);
    delay(300);
    noTone(buzzerPin);
    delay(100);
  }
}

// Stop the motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0); // Stop motor by setting speed to 0
}

// Hold the motors in place
void HoldMotors() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, 0); // Stop motor by setting speed to 0
}

// Check if the switch is on
bool isSwitchOn(int value) {
  return value > 1000; // Return true if analog reading is close to 1023 (switch on)
}

// Function to handle data received over I2C
void receiveEvent(int bytesReceived) {
  while (Wire.available()) {
    char c = Wire.read(); // Read one byte from I2C
    if (c == '-') {
      // Start of a new message
      receivedData = "-";
      receiving = true;
    } else if (c == '.' && receiving) {
      // End of the message
      receivedData += ".";
      receiving = false;
      lastReceiveTime = millis(); // Update the last received time
    } else if (receiving) {
      // Append to the message if we're in the middle of receiving
      receivedData += c;
    }
  }

  // Reset the timeout and process data immediately
  if (!receiving && receivedData.length() > 0) {
    lastReceiveTime = millis(); // Update the last received time
  }
}

// Function to print the lidar output data in the serial monitor
void printLidarData() {
  // Check if data was recently received
  if (millis() - lastReceiveTime <= timeoutDuration) {
    if (receivedData.length() > 0) {
      Serial.println(receivedData); // Print received data
    }
  } else {
    // Timeout occurred, clear the received data
    receivedData = ""; // Clear the string to avoid re-parsing old data
    Serial.println("0,0,0,0,0,0."); // Print zeros for timeout
    // Trigger special buzzer sound when printing zeros
    BuzzerRobotSpecial(); 
    StopMotors(); // Stop the robot if data is outdated

  }
}

// Motor control function
void controlRobot(int speedInput, int steeringInput) {
  // Map speedInput from -100 to 100 to motor speed range
  int motorSpeed = map(abs(speedInput), 0, 100, minSpeed, maxSpeed);
  
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

// Adjust robot control based on distance
void adjustControlBasedOnDistance() {
  int R = 25;  //requiredDistance
  int tolerance = 5;

  // Determine action based on the average distance
  if (FR < 15 || FL < 15 ) {
    void stepBack();

  } else if (FR < 30 || FL < 30 ) {
      controlRobot(50, 100);
  } else if (abs(R1 - R2) <= tolerance && abs(R1 - R) <= tolerance && abs(R2 - R) <= tolerance) {
      controlRobot(50, 0);
  } else if (R1<R2<R) {
      controlRobot(50, 0);
  } else if (R2<R1<R) {
      controlRobot(50, -50);
  } else if (R<R1<R2) {
      controlRobot(50, 50);
  } else if (R<R2<R1) {
      controlRobot(50, -50);
  } else {
    controlRobot(30, 0);
  }
}





// Robot action function
void act() {
  printLidarData();
  if (millis() - lastReceiveTime <= timeoutDuration) { // Only act if data is fresh
    parseMessage(receivedData);  // Parse the received data
    adjustControlBasedOnDistance(20); // Adjust based on required distance (30 cm)
  } else {
    StopMotors(); // Stop the robot if data is outdated
  }
}
void stepBack() {
  controlRobot(-100, -100);
  delay(500);
}
void setup() {
  Wire.begin(I2C_ADDRESS);          // Join the I2C bus with the specified address
  Wire.onReceive(receiveEvent);     // Register the receive event
  Serial.begin(9600);               // Start the Serial Monitor
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);  

  // Attach servo
  STEERING.attach(STEERING_SERVO_PIN);

  // Stop motors and set servo to neutral position
  StopMotors();
  controlRobot(0, 0);
  BuzzerRobotStart();
}

void loop() {
  int switchValue = analogRead(SWITCH_PIN); // Read the analog value of the switch

  if (isSwitchOn(switchValue)) { // Check if switch is on
    act();                       // Perform robot actions
  } else {
    StopMotors();                // Stop motors when the switch is off
    controlRobot(0, 0);          // Reset control
    BuzzerRobotError();
  }

  delay(100); // Short delay for stability
}
