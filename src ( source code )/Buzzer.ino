// Pin for the buzzer
const int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
}

// Function for Robot Start (series of short beeps)
void robotStart() {
  for (int i = 0; i < 10; i++) {    // 3 short beeps
    tone(buzzerPin, 1000);         // Frequency of 1000 Hz
    delay(200);                    // Beep for 200ms
    noTone(buzzerPin);             // Stop the beep
    delay(100);                    // Small pause
  }
}

// Function for Robot End (one long beep)
void robotEnd() {
  tone(buzzerPin, 500);            // Lower frequency for end sound
  delay(1000);                     // Long beep for 1 second
  noTone(buzzerPin);               // Stop the beep
}

// Function for Error (quick beeps)
void error() {
  for (int i = 0; i < 10; i++) {    // 5 quick beeps
    tone(buzzerPin, 1500);         // Higher frequency for error
    delay(100);                    // Beep for 100ms
    noTone(buzzerPin);             // Stop the beep
    delay(100);                    // Small pause
  }
}

// Function for Special (custom melody)
void special() {
  int melody[] = { 262, 294, 330, 349 };  // Notes for C, D, E, F
  for (int i = 0; i < 10; i++) {
    tone(buzzerPin, melody[i]);           // Play each note
    delay(300);                           // Hold for 300ms
    noTone(buzzerPin);                    // Stop the beep
    delay(100);                           // Pause between notes
  }
}

void loop() {
  // Example usage of the functions
  robotStart();   // Show robot start sound
  delay(2000);    // Wait for 2 seconds
  
  robotEnd();     // Show robot end sound
  delay(2000);    // Wait for 2 seconds
  
  error();        // Show error sound
  delay(2000);    // Wait for 2 seconds
  
  special();      // Play special sound
  delay(2000);    // Wait for 2 seconds
}
