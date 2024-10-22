#include <Servo.h>        // Include the Servo library
#include <VL53L1X.h>      // Include the VL53L1X sensor library
#include <Wire.h>         // Include the Wire library for I2C communication

// Define motors and sensor pins
#define ENA  11           // L298N EN_A motor speed
#define IN_1  13          // L298N in1 motor direction control
#define IN_2  12          // L298N in2 motor direction control
#define buzzerPin  8      // Pin for the buzzer
#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo
#define ENCODER_PIN_A 2  // D2 for encoder
#define ENCODER_PIN_B 3  // D3 for encoder

// Define sensor configuration
const uint8_t sensorCount = 4;  // Number of distance sensors
const uint8_t xshutPins[sensorCount] = { 4, 5, 6, 7 };  // XSHUT pins for the VL53L1X sensors

VL53L1X sensors[sensorCount];  // Sensor array

Servo STEERING;  // Create Servo object for steering

// Motor control variables
int MaxSpeed = 255;
int MinSpeed = 127;
int steeringAngle = 0;

volatile long encoderCount = 0;  // Track the encoder pulses
unsigned long lastTime = 0;      // Time for speed calculation
float motorSpeedRPM = 0;         // Motor speed in RPM

// Interrupt Service Routines for Encoder
void encoderISR_A() {
  encoderCount++;  // Increment pulse count on signal change
}
void encoderISR_B() {
  encoderCount--;  // Decrement pulse count on signal change (if using quadrature)
}

// Function to initialize the encoder
void setupEncoder() {
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);  // Set encoder pin A (D2)
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);  // Set encoder pin B (D3)

  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoderISR_A, CHANGE);  // Attach interrupt to pin A
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), encoderISR_B, CHANGE);  // Attach interrupt to pin B
}

// Function to read the current encoder count
long readEncoder() {
  return encoderCount;  // Return the pulse count
}

// Function to reset the encoder count
void resetEncoder() {
  encoderCount = 0;
}

// Function to drive the robot based on distance (in cm) and speed (-100 to 100)
void driveDistanceSpeed(float distanceCM, int speedInput) {
  // Set direction based on distance and speedInput
  if (distanceCM < 0 || speedInput < 0) {
    // Move backward if distance or speed is negative
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    distanceCM = abs(distanceCM);  // Use absolute distance for backward movement
    speedInput = abs(speedInput);  // Use absolute speed for backward movement
  } else {
    // Move forward if distance and speed are positive
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  }

  // Map speedInput from -100 to 100 to motor speed range (MinSpeed to MaxSpeed)
  int motorSpeed = map(abs(speedInput), 0, 100, MinSpeed, MaxSpeed);
  analogWrite(ENA, motorSpeed);

  // Reset encoder count before starting the movement
  resetEncoder();

  // Assuming the encoder gives 11 pulses per revolution and we know the wheel circumference
  // Wheel circumference should be in centimeters
  float pulsesPerRevolution = 11.0;  // Adjust if necessary
  float wheelDiameterCM = 6.8;  // Example: wheel diameter of 6.8 cm (adjust based on your wheel size)
  float wheelCircumferenceCM = PI * wheelDiameterCM;  // Calculate wheel circumference in cm

  // Calculate the required number of pulses for the given distance in cm
  float pulsesRequired = (distanceCM / wheelCircumferenceCM) * pulsesPerRevolution;

  // Move the robot until the encoder count reaches the required distance
  while (abs(readEncoder()) < pulsesRequired) {
    // Continuously move the robot until the required distance is reached
    delay(10);  // Small delay for smooth operation
  }

  // Stop the motors after reaching the distance
  StopMotors();
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
  steeringAngle = map(steeringInput, -100, 100, 130, 50);

  // Set servo position
  STEERING.write(steeringAngle);
}

// Existing sensor functions
void setupSensors() {
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }
  
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1);  // Halt execution if sensor initialization fails
    }

    sensors[i].setAddress(0x2A + i);
    sensors[i].startContinuous(50);  // Start continuous measurement
  }
}

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

void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);  // Stop motor by setting speed to 0
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

// Setup function
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);  // Set I2C clock speed

  // Initialize motor and buzzer pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize Steering Servo
  STEERING.attach(STEERING_SERVO_PIN);

  StopMotors();  // Ensure motors are stopped initially

  setupSensors();  // Initialize sensors
  setupEncoder();  // Initialize encoder

  BuzzerRobotStart();  // Play the start sound
}

// Loop function
void loop() {

}
