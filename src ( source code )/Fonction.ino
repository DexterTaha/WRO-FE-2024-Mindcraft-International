#include <Servo.h>  // Include the Servo library
#include <VL53L1X.h>
#include <Wire.h>


#define ENA  11         // L298N EN_A motors Speed
#define IN_1  13        // L298N in1 motors Right
#define IN_2  12        // L298N in2 motors Right
#define buzzerPin  8    // Pin for the buzzer

// The number of sensors in your system.
const uint8_t sensorCount = 4;

// The Arduino pin connected to the XSHUT pin of each sensor.
const uint8_t xshutPins[sensorCount] = { 4, 5, 6, 7 };
// 4: back
// 5: left
// 6: front
// 7: right

VL53L1X sensors[sensorCount];

// Pin for the buzzer
Servo STEERING;         // Create Servo object for the STEERING

int MaxSpeed = 255;
int MinSpeed = 0;
int speed = 0;
int steeringAngle = 0;

// Function to control speed, direction, and steering
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

// Function to setup the VL53L1X sensors
void setupSensors()
{
  // Disable/reset all sensors by driving their XSHUT pins low.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }

  // Enable, initialize, and start each sensor, one by one.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    // Stop driving this sensor's XSHUT low and wait for startup.
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init())
    {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1);
    }

    // Change the address of the sensor to a unique value.
    sensors[i].setAddress(0x2A + i);

    // Start continuous measurements with an interval of 50 ms.
    sensors[i].startContinuous(50);
  }
}

// Function to read and print distances from the sensors
void readAndPrintDistances()
{
  // Front sensor
  Serial.print("F: ");
  Serial.print(sensors[2].read());
  if (sensors[2].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print('\t');

  // Right sensor
  Serial.print("R: ");
  Serial.print(sensors[3].read());
  if (sensors[3].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print('\t');

  // Left sensor
  Serial.print("L: ");
  Serial.print(sensors[1].read());
  if (sensors[1].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print('\t');

  // Back sensor
  Serial.print("B: ");
  Serial.print(sensors[0].read());
  if (sensors[0].timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.print('\t');

  Serial.println();
  delay(50);  // Optional delay to match the sensor's continuous reading interval
}

// Function for Robot Start (series of short beeps)
void BuzzerRobotStart() {
  for (int i = 0; i < 10; i++) {    // 3 short beeps
    tone(buzzerPin, 1000);         // Frequency of 1000 Hz
    delay(200);                    // Beep for 200ms
    noTone(buzzerPin);             // Stop the beep
    delay(100);                    // Small pause
  }
}

// Function for Robot End (one long beep)
void BuzzerRobotEnd() {
  tone(buzzerPin, 500);            // Lower frequency for end sound
  delay(1000);                     // Long beep for 1 second
  noTone(buzzerPin);               // Stop the beep
}

// Function for Error (quick beeps)
void BuzzerRoboterror() {
  for (int i = 0; i < 10; i++) {    // 5 quick beeps
    tone(buzzerPin, 1500);         // Higher frequency for error
    delay(100);                    // Beep for 100ms
    noTone(buzzerPin);             // Stop the beep
    delay(100);                    // Small pause
  }
}

// Function for Special (custom melody)
void BuzzerRobotspecial() {
  int melody[] = { 262, 294, 330, 349 };  // Notes for C, D, E, F
  for (int i = 0; i < 10; i++) {
    tone(buzzerPin, melody[i]);           // Play each note
    delay(300);                           // Hold for 300ms
    noTone(buzzerPin);                    // Stop the beep
    delay(100);                           // Pause between notes
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  
  // Attach the servo to the correct pin (example: pin 9)
  STEERING.attach(9);

  // Initialize motors to stopped state
  StopMotors();

  setupSensors();  // Initialize all sensors
}

void loop() {
  // Example: test the function by passing speed and steering values
  controlRobot(50, 0);  // Move forward with 50% speed, neutral steering
  delay(2000);

  controlRobot(-50, 50);  // Move backward with 50% speed, steer to the right
  delay(2000);

  controlRobot(100, -100);  // Move forward with full speed, steer to the left
  delay(2000);

  StopMotors();  // Stop the motors after the loop ends
}

// Stop motors function
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
}
