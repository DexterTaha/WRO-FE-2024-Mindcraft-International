#include <Servo.h>          // Include the Servo library
#include <Wire.h>           // Include Wire library for I2C communication
#include <MPU6050.h>        // Include MPU6050 library

// ---------------------------
// Motor Control Definitions
// ---------------------------
#define ENA  11             // L298N EN_A motor speed control
#define IN_1  13            // L298N IN1 for motor direction
#define IN_2  12            // L298N IN2 for motor direction

// ---------------------------
// Servo Control Definitions
// ---------------------------
#define STEERING_SERVO_PIN 10  // Servo control pin

Servo STEERING;             // Create Servo object

// ---------------------------
// MPU6050 Definitions
// ---------------------------
MPU6050 mpu;

// Variables to store raw gyro readings
int16_t rawGyroZ;

// Variables to store converted gyro readings in degrees per second
float gyroZ;

// Calibration offsets
float gyroOffsetZ = 0.0;

// Gyroscope scale factor based on full-scale range (±250°/s)
const float GYRO_SCALE = 250.0 / 32768.0;

// Threshold to determine significant rotation (adjust as needed)
const float ROTATION_THRESHOLD = 10.0; // in degrees per second

// Accumulated rotation
float accumulatedRotationZ = 0.0;

// ---------------------------
// Speed and Steering Parameters
// ---------------------------
const int MaxSpeed = 255;
const int MinSpeed = 0;
int steeringAngle = 0;

// ---------------------------
// Timing Definitions
// ---------------------------
unsigned long previousTime = 0;

// ---------------------------
// Function Prototypes
// ---------------------------
void controlRobot(int speedInput, int steeringInput);
void StopMotors();
bool initializeMPU6050();
void calibrateGyroscope();
void turn90Degrees();

// ---------------------------
// Robot Control Function
// ---------------------------
void robotControl() {
  // Example behavior: Move forward for 2 seconds, turn 90 degrees, repeat
  
  // Move forward
  controlRobot(100, 0);  // 50% speed, neutral steering
  delay(1000);          // Move forward for 2 seconds
  
  // Turn 90 degrees to the right
  turn90Degrees();
  
  // Move forward again
  controlRobot(100, 0);  // 50% speed, neutral steering
  delay(1000);          // Move forward for 2 seconds
  
  // Turn 90 degrees to the right
  turn90Degrees();
  
  // Stop after completing actions
  StopMotors();
  delay(1000);          // Wait for 2 seconds before repeating
}

// ---------------------------
// Control Robot Function
// ---------------------------
void controlRobot(int speedInput, int steeringInput) {
  // Map speedInput from -100 to 100 to motor speed range 0 to MaxSpeed
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
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
  }

  // Set motor speed
  analogWrite(ENA, motorSpeed);

  // Map steeringInput from -100 to 100 to servo angle range 130 to 50 degrees
  steeringAngle = map(steeringInput, -100, 100, 130, 50);

  // Set servo position
  STEERING.write(steeringAngle);
}

// ---------------------------
// Stop Motors Function
// ---------------------------
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
  STEERING.write(90); // Center steering
}

// ---------------------------
// Initialize MPU6050 Function
// ---------------------------
bool initializeMPU6050() {
  Wire.begin();
  mpu.initialize();
  
  // Check connection
  if (!mpu.testConnection()) {
    return false;
  }
  
  // Configure the gyro sensitivity (±250°/s)
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  
  return true;
}

// ---------------------------
// Calibrate Gyroscope Function
// ---------------------------
void calibrateGyroscope() {
  Serial.println("Calibrating gyroscope. Please keep the robot stationary.");
  int numSamples = 100;
  long sumZ = 0;
  
  for (int i = 0; i < numSamples; i++) {
    rawGyroZ = mpu.getRotationZ(); // Corrected function call
    sumZ += rawGyroZ;
    delay(10); // Adjust delay based on desired sample rate
  }
  
  gyroOffsetZ = ((float)sumZ / numSamples) * GYRO_SCALE;
  
  Serial.println("Gyroscope calibration complete.");
  Serial.print("Gyro Offset Z: "); Serial.print(gyroOffsetZ, 2); Serial.println(" °/s");
}

// ---------------------------
// Turn 90 Degrees Function
// ---------------------------
void turn90Degrees() {
    Serial.println("Initiating 90-degree turn...");

    // Reset accumulated rotation
    accumulatedRotationZ = 0.0;

    // Set previous time for delta time calculation
    previousTime = millis();

    // Start turning to the right at a higher speed
    int turnSpeed = 200;  // Set a constant high speed (80% or more)
    controlRobot(turnSpeed, 100);  // High speed, full steering to the right

    while (abs(accumulatedRotationZ) < 90.0) {
        // Read gyro data
        rawGyroZ = mpu.getRotationZ();
        gyroZ = ((float)rawGyroZ) * GYRO_SCALE - gyroOffsetZ;

        // Get current time
        unsigned long currentTime = millis();

        // Calculate delta time in seconds
        float deltaTime = (currentTime - previousTime) / 1000.0;
        previousTime = currentTime;

        // Calculate angle change
        float angleChange = gyroZ * deltaTime;

        // Accumulate rotation
        accumulatedRotationZ += angleChange;

        // Debugging output
        Serial.print("Gyro Z: "); Serial.print(gyroZ, 2); Serial.print(" °/s\t");
        Serial.print("Accumulated Rotation Z: "); Serial.print(accumulatedRotationZ, 2); Serial.println(" °");

        delay(10); // Small delay to prevent excessive serial output
    }

    // Stop turning
    StopMotors();
    Serial.println("90-degree turn complete!");

    delay(1000); // Brief pause after turning
}

// ---------------------------
// Setup Function
// ---------------------------
void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for Serial to be ready

  // Initialize Motor Control Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  
  // Initialize Steering Servo
  STEERING.attach(STEERING_SERVO_PIN);
  
  // Initialize motors to stopped state
  StopMotors();
  
  // Initialize MPU6050
  if (!initializeMPU6050()) {
    Serial.println("Failed to initialize MPU6050. Check connections.");
    while (1); // Halt if initialization fails
  }
  
  // Calibrate Gyroscope
  calibrateGyroscope();
  Serial.println("Calibration complete. Starting operation.");
}

// ---------------------------
// Loop Function
// ---------------------------
void loop() {
  // Call the main robot control function
  robotControl();
}
