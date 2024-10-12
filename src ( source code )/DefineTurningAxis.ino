#include <Wire.h>
#include <MPU6050.h>

// Create an MPU6050 object
MPU6050 mpu;

// Variables to store raw gyro readings
int16_t rawGyroX, rawGyroY, rawGyroZ;

// Variables to store converted gyro readings in degrees per second
float gyroX, gyroY, gyroZ;

// Calibration offsets
float gyroOffsetX = 0.0, gyroOffsetY = 0.0, gyroOffsetZ = 0.0;

// Gyroscope scale factor based on full-scale range (±250°/s)
const float GYRO_SCALE = 250.0 / 32768.0;

// Threshold to determine significant rotation (adjust as needed)
const float ROTATION_THRESHOLD = 10.0; // in degrees per second

// Duration for calibration (in number of samples)
const int CALIBRATION_SAMPLES = 100;

// Function Prototypes
bool initializeMPU6050();
void calibrateGyroscope();
void determineTurningAxis(String &axis);

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for Serial to be ready
  
  Serial.println("Initializing MPU6050...");
  
  // Initialize MPU6050
  if (!initializeMPU6050()) {
    Serial.println("Failed to initialize MPU6050. Check connections.");
    while (1); // Halt if initialization fails
  }
  
  // Calibrate Gyroscope
  calibrateGyroscope();
  Serial.println("Calibration complete. Starting rotation detection.");
}

void loop() {
  // Read raw gyroscope data
  mpu.getRotation(&rawGyroX, &rawGyroY, &rawGyroZ);
  
  // Convert raw gyro data to degrees per second and apply offsets
  gyroX = ((float)rawGyroX) * GYRO_SCALE - gyroOffsetX;
  gyroY = ((float)rawGyroY) * GYRO_SCALE - gyroOffsetY;
  gyroZ = ((float)rawGyroZ) * GYRO_SCALE - gyroOffsetZ;
  
  // Determine the turning axis
  String turningAxis = "None";
  determineTurningAxis(turningAxis);
  
  // Print gyro data and turning axis
  Serial.print("Gyro X: "); Serial.print(gyroX, 2); Serial.print(" °/s\t");
  Serial.print("Gyro Y: "); Serial.print(gyroY, 2); Serial.print(" °/s\t");
  Serial.print("Gyro Z: "); Serial.print(gyroZ, 2); Serial.print(" °/s\t");
  Serial.print("Turning Axis: "); Serial.println(turningAxis);
  
  delay(500); // Adjust delay as needed
}

// Function to initialize MPU6050
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

// Function to calibrate the gyroscope
void calibrateGyroscope() {
  Serial.println("Calibrating gyroscope. Please keep the robot stationary.");
  long sumX = 0, sumY = 0, sumZ = 0;
  
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    mpu.getRotation(&rawGyroX, &rawGyroY, &rawGyroZ);
    sumX += rawGyroX;
    sumY += rawGyroY;
    sumZ += rawGyroZ;
    delay(10); // Adjust delay based on sample rate
  }
  
  gyroOffsetX = ((float)sumX / CALIBRATION_SAMPLES) * GYRO_SCALE;
  gyroOffsetY = ((float)sumY / CALIBRATION_SAMPLES) * GYRO_SCALE;
  gyroOffsetZ = ((float)sumZ / CALIBRATION_SAMPLES) * GYRO_SCALE;
  
  Serial.println("Gyroscope calibration complete.");
  Serial.print("Gyro Offsets - X: "); Serial.print(gyroOffsetX, 2);
  Serial.print(" °/s, Y: "); Serial.print(gyroOffsetY, 2);
  Serial.print(" °/s, Z: "); Serial.print(gyroOffsetZ, 2); Serial.println(" °/s");
}

// Function to determine the turning axis based on gyro data
void determineTurningAxis(String &axis) {
  // Calculate absolute gyro values
  float absGyroX = abs(gyroX);
  float absGyroY = abs(gyroY);
  float absGyroZ = abs(gyroZ);
  
  // Initialize variables to track the highest rotation
  float maxGyro = 0.0;
  
  if (absGyroX > ROTATION_THRESHOLD || absGyroY > ROTATION_THRESHOLD || absGyroZ > ROTATION_THRESHOLD) {
    if (absGyroX > absGyroY && absGyroX > absGyroZ) {
      maxGyro = absGyroX;
      axis = "X-axis (Roll)";
    }
    else if (absGyroY > absGyroX && absGyroY > absGyroZ) {
      maxGyro = absGyroY;
      axis = "Y-axis (Pitch)";
    }
    else {
      maxGyro = absGyroZ;
      axis = "Z-axis (Yaw)";
    }
  }
  else {
    axis = "None";
  }
}
