#include <Servo.h>        // Include the Servo library
#include <VL53L1X.h>      // Include the VL53L1X sensor library
#include <Wire.h>         // Include the Wire library for I2C communication

// Define motor and sensor pins
#define ENA  11           // L298N EN_A motor speed
#define IN_1  13          // L298N in1 motor direction control (right motor)
#define IN_2  12          // L298N in2 motor direction control (right motor)
#define buzzerPin  8      // Pin for the buzzer

// Define sensor configuration
const uint8_t sensorCount = 4;  // Number of distance sensors
const uint8_t xshutPins[sensorCount] = { 4, 5, 6, 7 };  // XSHUT pins for the VL53L1X sensors

VL53L1X sensors[sensorCount];  // Sensor array

Servo STEERING;  // Create Servo object for steering

// Motor control variables
int MaxSpeed = 255;
int MinSpeed = 0;
int steeringAngle = 0;

// Setup function to control speed, direction, and steering
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
  steeringAngle = map(steeringInput, -100, 100, 130, 50);

  // Set servo position
  STEERING.write(steeringAngle);
}

// Function to setup the VL53L1X sensors
void setupSensors() {
  // Disable/reset all sensors by driving their XSHUT pins low
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }

  // Enable and initialize each sensor
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1);  // Halt execution if sensor initialization fails
    }

    // Set a unique address for each sensor
    sensors[i].setAddress(0x2A + i);
    sensors[i].startContinuous(50);  // Start continuous measurement
  }
}

// Function to read and print distances from the sensors
void readAndPrintDistances() {
  Serial.print("F: ");
  Serial.print(sensors[2].read());
  if (sensors[2].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print("\t");

  Serial.print("R: ");
  Serial.print(sensors[3].read());
  if (sensors[3].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print("\t");

  Serial.print("L: ");
  Serial.print(sensors[1].read());
  if (sensors[1].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print("\t");

  Serial.print("B: ");
  Serial.print(sensors[0].read());
  if (sensors[0].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

  delay(50);  // Delay to match the sensor's continuous reading interval
}

// Function to stop the motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);  // Stop motor by setting speed to 0
}

// Buzzer functions
void BuzzerRobotStart() {
  for (int i = 0; i < 3; i++) {  // 3 short beeps
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
  for (int i = 0; i < 5; i++) {  // 5 quick beeps
    tone(buzzerPin, 1500);  // Higher frequency for error
    delay(100);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotSpecial() {
  int melody[] = { 262, 294, 330, 349 };  // Notes for C, D, E, F
  for (int i = 0; i < 4; i++) {  // Play the melody
    tone(buzzerPin, melody[i]);
    delay(300);
    noTone(buzzerPin);
    delay(100);
  }
}

// Setup function for initialization
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);  // Set I2C clock speed

  // Initialize motor and buzzer pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Attach the servo to pin 9
  STEERING.attach(9);

  StopMotors();  // Ensure motors are stopped initially

  setupSensors();  // Initialize sensors

  BuzzerRobotStart();  // Play the start sound
}

// Loop function for continuous operation
void loop() {
  // Test the robot's movement with different speeds and steering angles
  controlRobot(50, 0);  // Move forward with 50% speed, neutral steering
  delay(2000);

  controlRobot(-50, 50);  // Move backward with 50% speed, steer right
  delay(2000);

  controlRobot(100, -100);  // Move forward with full speed, steer left
  delay(2000);

  StopMotors();  // Stop the motors after the loop

  readAndPrintDistances();  // Read and print sensor distances
}
