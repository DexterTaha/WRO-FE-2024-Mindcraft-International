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
int steeringAngle = 90; // Neutral steering position

// Variables to store the parsed values
int FR = 0, FL = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;

// Variable to count increments
int counter = 0;
unsigned long lastCounterUpdateTime = 0; // Time when the counter was last incremented
const unsigned long counterDelay = 3000; // 3 seconds in milliseconds

// Debounce timing
unsigned long lastSwitchCheck = 0;
const unsigned long debounceDelay = 50;

// Function to parse the received message
void parseMessage(String message) {
  if (message.startsWith("-") && message.endsWith(".")) {
    message = message.substring(1, message.length() - 1);

    int firstComma = message.indexOf(',');
    int secondComma = message.indexOf(',', firstComma + 1);
    int thirdComma = message.indexOf(',', secondComma + 1);
    int fourthComma = message.indexOf(',', thirdComma + 1);
    int fifthComma = message.indexOf(',', fourthComma + 1);

    FR = message.substring(0, firstComma).toInt();
    FL = message.substring(firstComma + 1, secondComma).toInt();
    L1 = message.substring(secondComma + 1, thirdComma).toInt();
    L2 = message.substring(thirdComma + 1, fourthComma).toInt();
    R1 = message.substring(fourthComma + 1, fifthComma).toInt();
    R2 = message.substring(fifthComma + 1).toInt();
  } else {
    Serial.println("Error: Invalid message format");
  }
}

// Buzzer functions
void BuzzerRobotStart() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotEnd() {
  tone(buzzerPin, 500);
  delay(1000);
  noTone(buzzerPin);
}

void BuzzerRobotError() {
  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  }
}

void BuzzerRobotSpecial() {
  int melody[] = { 262, 294, 330, 349 };
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, melody[i]);
    delay(300);
    noTone(buzzerPin);
    delay(100);
  }
}

// Stop motors
void StopMotors() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
}

// Hold motors
void HoldMotors() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, 0);
}

// Check if switch is on
bool isSwitchOn(int value) {
  return value > 1000;
}

// Handle data received over I2C
void receiveEvent(int bytesReceived) {
  while (Wire.available()) {
    char c = Wire.read();
    if (c == '-') {
      receivedData = "-";
      receiving = true;
    } else if (c == '.' && receiving) {
      receivedData += ".";
      receiving = false;
      lastReceiveTime = millis();
    } else if (receiving) {
      receivedData += c;
    }
  }
}

// Control robot motors
void controlRobot(int speedInput, int steeringInput) {
  int motorSpeed = map(abs(speedInput), 0, 100, minSpeed, maxSpeed);

  if (speedInput > 0) {
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  } else if (speedInput < 0) {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
  } else {
    StopMotors();
    return;
  }

  analogWrite(ENA, motorSpeed);
  steeringAngle = map(steeringInput, -100, 100, 60, 120);
  STEERING.write(steeringAngle);
}

// Adjust control based on distance
void adjustControlBasedOnDistance() {
  if (R2 > 100) {
    controlRobot(30, 50);
  } else if (R2 > 150 && millis() - lastCounterUpdateTime > counterDelay) {
    counter++;
    lastCounterUpdateTime = millis();

    // Print the updated counter value
    Serial.print("Counter: ");
    Serial.println(counter);
  } else if (R2 >= 25 && R2 <= 35) {
    controlRobot(30, 0);
  } else if (R2 < 30) {
    controlRobot(30, -50);
  } else if (R2 > -30) {
    controlRobot(30, 50);
  }
}

void act() {
  if (millis() - lastReceiveTime <= timeoutDuration) {
    parseMessage(receivedData);
    adjustControlBasedOnDistance();
  } else {
    StopMotors();
    BuzzerRobotSpecial();
  }
}

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  STEERING.attach(STEERING_SERVO_PIN);

  StopMotors();
  BuzzerRobotStart();
  Serial.println("on");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSwitchCheck > debounceDelay) {
    lastSwitchCheck = currentTime;
    int switchValue = analogRead(SWITCH_PIN);

    if (isSwitchOn(switchValue)) {
      act();
    } else {
      StopMotors();
      BuzzerRobotError();
      Serial.println("ready");
    }
  }
}
