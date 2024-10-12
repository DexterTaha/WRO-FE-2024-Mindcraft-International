#include <Servo.h>  // Include the Servo library

#define ENA  11         // L298N EN_A motors Speed
#define IN_1  13        // L298N in1 motors Right
#define IN_2  12        // L298N in2 motors Right

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

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  
  // Attach the servo to the correct pin (example: pin 9)
  STEERING.attach(9);

  // Initialize motors to stopped state
  StopMotors();
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
