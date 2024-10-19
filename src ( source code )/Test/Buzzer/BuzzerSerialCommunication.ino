const int buzzerPin = 8; // Pin connected to the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set pin 8 as output
  Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    char command = Serial.read(); // Read the incoming byte

    if (command == '1') { // If the command is '1'
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    } else if (command == '0') { // If the command is '0'
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    }
  }
}
