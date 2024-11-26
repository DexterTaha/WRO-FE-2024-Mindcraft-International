
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
int steeringAngle = 0;

// Variables to store the parsed values
int FR = 0, FL = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;

// Variable to count increments
int counter = 0;
unsigned long lastCounterUpdateTime = 0; // Time when the counter was last incremented
const unsigned long counterDelay = 3000; // 5 seconds in milliseconds

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

  if (!receiving && receivedData.length() > 0) {
    lastReceiveTime = millis();
  }
}

// Print LIDAR data
void printLidarData() {
  if (millis() - lastReceiveTime <= timeoutDuration) {
    if (receivedData.length() > 0) {
      Serial.println(receivedData);
    }
  } else {
    receivedData = "";
    Serial.println("0,0,0,0,0,0.");
    BuzzerRobotSpecial();
    StopMotors();
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
  }

  analogWrite(ENA, motorSpeed);
  steeringAngle = map(steeringInput, -100, 100, 120, 60);
  STEERING.write(steeringAngle);
}

// Adjust control based on distance
void adjustControlBasedOnDistance() {
  int R = 20;
  int tolerance = 5;

  if (R1 > 150 && R2 > 150) {
    controlRobot(50, 100);
  } else if (R1 > 150 && R2 > 150 && millis() - lastCounterUpdateTime > counterDelay) {
    counter++;
    lastCounterUpdateTime = millis();

    // Print the updated counter value
    Serial.print("Counter: ");
    Serial.println(counter);

    delay(counterDelay); // Pause for 5 seconds
  } else if (abs(R1 - R2) <= tolerance && abs(R1 - R) <= tolerance) {
    controlRobot(100, 0);
  } else if (R1 < R && R2 < R && R1 < R2) {
    controlRobot(30, 0);
  } else if (R2 < R1 && R1 < R && R2 < R) {
    controlRobot(30, -80);
  } else if (R < R1 && R1 < R2 && R < R2) {
    controlRobot(30, 80);
  } else if (R < R2 && R2 < R1 && R < R1) {
    controlRobot(30, -80);
  } else if (FR < 15 || FL < 15) {
    Serial.println("stepBack");
    stepBack();
  } else {
    controlRobot(30, 0);
  }
}

void stepBack() {
  controlRobot(-100, -100);
}

void act() {
  printLidarData();
  if (millis() - lastReceiveTime <= timeoutDuration) {
    parseMessage(receivedData);
    adjustControlBasedOnDistance();
  } else {
    StopMotors();
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
  controlRobot(0, 0);
  BuzzerRobotStart();
  Serial.println("on");
}

void loop() {
  int switchValue = analogRead(SWITCH_PIN);

  if (isSwitchOn(switchValue)) {
    act();
  } else {
    StopMotors();
    controlRobot(0, 0);
    BuzzerRobotError();
    Serial.println("ready");

  }

  delay(100);
}
