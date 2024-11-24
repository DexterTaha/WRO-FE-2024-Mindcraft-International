#include <Wire.h>
#include <Servo.h>

#define I2C_ADDRESS 0x08  // I2C address of this Arduino

// Define the switch pin
#define switchPin  A0  // Switch pin

String receivedData = "";  // String to store the incoming message
bool receiving = false;    // Flag to check if we are in the middle of receiving a message

// Motor control pins
#define ENA  11
#define IN_1 13
#define IN_2 12

#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo

Servo steeringServo;  // Create Servo object for steering

// Motor control variables
int MaxSpeed = 255;
int MinSpeed = 127;
int steeringAngle = 0;

// Buzzer functions (no longer used for now)
void BuzzerRobotError() {
  for (int i = 0; i < 5; i++) {
    tone(8, 1500);  // Tone at 1500Hz (you can change the pin if needed)
    delay(100);
    noTone(8);  // Stop tone
    delay(100);
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

  // Map steeringInput from -100 to 100 to servo angle range (130 to 50 degrees)
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
  steeringServo.attach(STEERING_SERVO_PIN);
  // Stop and hold motors when the switch is off
  StopMotors();  
  // Stop motors and set servo to neutral position
  controlRobot(0, 0);
}

void loop() {
  int switchValue = analogRead(switchPin);  // Read the analog value of the switch

  if (isSwitchOn  (switchValue)) {  // Check if switch is on
    act();  // Perform robot actions when the switch is on
  } else {
    StopMotors();  // Stop and hold motors when the switch is off
    controlRobot(0, 0);
    BuzzerRobotError();  // Play error sound
  }

  delay(100);  // Short delay for stability
}
