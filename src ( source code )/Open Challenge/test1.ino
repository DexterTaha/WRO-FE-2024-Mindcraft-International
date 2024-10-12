#include <Servo.h>          // Include the Servo library
#include <Wire.h>
#include <VL53L1X.h>

// Motor Control Pins
#define ENA  11             // L298N EN_A motors Speed
#define IN_1  13            // L298N in1 motors Right
#define IN_2  12            // L298N in2 motors Right

// Servo Control
#define STEERING_SERVO_PIN 10  // Pin connected to the steering servo

Servo STEERING;             // Create Servo object for the STEERING

// Speed Parameters
const int MaxSpeed = 255;
const int MinSpeed = 0;

// Sensor Configuration
const uint8_t sensorCount = 4;
const uint8_t xshutPins[sensorCount] = {4, 5, 6, 7}; // 4: Back, 5: Left, 6: Front, 7: Right
VL53L1X sensors[sensorCount];

// Target Distances (in mm)
const int TARGET_RIGHT_DISTANCE = 300;   // Desired distance from the right wall
const int TARGET_FRONT_DISTANCE = 200;   // Distance to trigger obstacle avoidance

// PID Control Parameters for Steering
const float Kp = 0.5;  // Proportional gain
const float Kd = 0.1;  // Derivative gain

// Variables for PID
float previousError = 0;

// Function Prototypes
void controlRobot(int speedInput, int steeringInput);
void StopMotors();
void setupSensors();
void readSensors(int &frontDist, int &rightDist, int &leftDist, int &backDist);

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  while (!Serial) {}

  // Initialize Motor Control Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  
  // Initialize Steering Servo
  STEERING.attach(STEERING_SERVO_PIN);
  StopMotors(); // Ensure motors are stopped initially

  // Initialize Sensors
  setupSensors();
}

void loop() {
  int frontDistance, rightDistance, leftDistance, backDistance;
  
  // Read sensor distances
  readSensors(frontDistance, rightDistance, leftDistance, backDistance);
  
  // Debug: Print sensor readings
  Serial.print("Front: "); Serial.print(frontDistance);
  Serial.print(" mm\tRight: "); Serial.print(rightDistance);
  Serial.print(" mm\tLeft: "); Serial.print(leftDistance);
  Serial.print(" mm\tBack: "); Serial.print(backDistance);
  Serial.println(" mm");
  
  // Check for obstacle in front
  if (frontDistance < TARGET_FRONT_DISTANCE) {
    // Obstacle detected, perform avoidance maneuver
    // Example: Stop and turn left
    controlRobot(0, 0); // Stop
    delay(500);
    controlRobot(50, -50); // Move forward with slight left steering
    delay(1000);
    // You can enhance this with more complex maneuvers
  } else {
    // Wall Following Logic
    // Calculate error between target and actual right distance
    float error = TARGET_RIGHT_DISTANCE - rightDistance;
    
    // Calculate derivative of error
    float derivative = error - previousError;
    
    // PID controller for steering
    float steeringAdjustment = Kp * error + Kd * derivative;
    
    // Map steering adjustment to steering input (-100 to 100)
    int steeringInput = constrain((int)(steeringAdjustment), -100, 100);
    
    // Determine speed based on how parallel we are to the wall
    // If error is large, slow down to correct
    int speedInput = 80; // Base speed
    if (abs(error) > 100) {
      speedInput = 60;
    }
    
    // Update previous error
    previousError = error;
    
    // Control the robot with computed speed and steering
    controlRobot(speedInput, steeringInput);
  }
  
  delay(100); // Short delay for loop stability
}

// Function to control speed, direction, and steering
void controlRobot(int speedInput, int steeringInput) {
  // Determine direction based on speedInput
  if (speedInput > 0) {
    // Move forward
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  } else if (speedInput < 0) {
    // Move backward
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    speedInput = abs(speedInput); // Ensure speed is positive for mapping
  } else {
    // Stop motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
  }

  // Map speedInput from 0-100 to 0-255
  int motorSpeed = map(constrain(abs(speedInput), 0, 100), 0, 100, MinSpeed, MaxSpeed);
  
  // Set motor speed
  analogWrite(ENA, motorSpeed);
  
  // Map steeringInput from -100 to 100 to servo angle 130 to 50 degrees
  int steeringAngle = map(constrain(steeringInput, -100, 100), -100, 100, 130, 50);
  
  // Set servo position
  STEERING.write(steeringAngle);
}

// Function to stop motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
  STEERING.write(90); // Center steering
}

// Function to initialize sensors
void setupSensors() {
  Wire.begin();
  Wire.setClock(400000); // Use 400 kHz I2C
  
  // Disable/reset all sensors by driving their XSHUT pins low.
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }
  
  delay(10); // Ensure all sensors are reset
  
  // Enable, initialize, and start each sensor, one by one.
  for (uint8_t i = 0; i < sensorCount; i++) {
    // Enable the sensor by setting XSHUT high (input mode)
    pinMode(xshutPins[i], INPUT);
    delay(10); // Wait for sensor to boot up
    
    // Initialize the sensor
    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1); // Halt if any sensor fails
    }
    
    // Set a unique I2C address
    sensors[i].setAddress(0x2A + i);
    
    // Start continuous measurement
    sensors[i].startContinuous(50); // 50 ms timing budget
  }
}

// Function to read sensor distances
void readSensors(int &frontDist, int &rightDist, int &leftDist, int &backDist) {
  frontDist = sensors[2].read();  // Front sensor
  if (sensors[2].timeoutOccurred()) { frontDist = -1; }
  
  rightDist = sensors[3].read();  // Right sensor
  if (sensors[3].timeoutOccurred()) { rightDist = -1; }
  
  leftDist = sensors[1].read();   // Left sensor
  if (sensors[1].timeoutOccurred()) { leftDist = -1; }
  
  backDist = sensors[0].read();   // Back sensor
  if (sensors[0].timeoutOccurred()) { backDist = -1; }
}
