#include <Servo.h>        // Include the Servo library
#include <VL53L1X.h>      // Include the VL53L1X sensor library
#include <Wire.h>         // Include the Wire library for I2C communication

// Define motors and sensor pins
#define ENA  11           // L298N EN_A motor speed
#define IN_1  13          // L298N in1 motor direction control
#define IN_2  12          // L298N in2 motor direction control
#define buzzerPin  8      // Pin for the buzzer
#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo

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
  pinMode(2, INPUT_PULLUP);  // Set encoder pin D2
  pinMode(3, INPUT_PULLUP);  // Set encoder pin D3

  attachInterrupt(digitalPinToInterrupt(2), encoderISR_A, CHANGE);  // Attach interrupt to D2
  attachInterrupt(digitalPinToInterrupt(3), encoderISR_B, CHANGE);  // Attach interrupt to D3
}

// Function to read the current encoder count
long readEncoder() {
  return encoderCount;  // Return the pulse count
}

// Function to reset the encoder count
void resetEncoder() {
  encoderCount = 0;
}

// Function to stop the motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);  // Stop motor by setting speed to 0
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

  // Initialize Steering Servo
  STEERING.attach(STEERING_SERVO_PIN);

  StopMotors();  // Ensure motors are stopped initially

  setupEncoder();  // Initialize encoder

  BuzzerRobotStart();  // Play the start sound
}

// Loop function for continuous operation
void loop() {
  // Test driving forward for 100 cm at 50% speed
  driveDistanceSpeed(100.0, 50);  
  delay(2000);  // Wait for 2 seconds
  
  // Test driving backward for 50 cm at 30% speed
  driveDistanceSpeed(-50.0, -30);
  delay(2000);  // Wait for 2 seconds
  
  // Repeat or add other driving patterns as needed
}
