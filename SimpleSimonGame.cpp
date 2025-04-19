#include <Arduino.h>
// Simple Simon Game
// This is a simple Simon game where the user has to repeat a sequence of lights.
// The game starts with a random sequence of lights, and the user has to press the buttons in the same order.
// If the user presses the wrong button, the game ends and a lose sequence is played.
// If the user successfully completes the sequence, a win sequence is played.
// The game continues until the user loses or completes the maximum number of levels.
// The game uses 4 LEDs and 4 buttons.
// The LEDs are connected to pins 2, 3, 4, and 5.
// The buttons are connected to pins 8, 9, 10, and 11.
// The LEDs are turned on and off to indicate the sequence.
// The buttons are used to input the user's response.
// The game uses a random number generator to create the sequence.
// The game uses a delay to create a pause between the LED sequences and the user's response.
// The game uses a serial monitor to display the sequence and the user's response.
// The game uses a random seed based on the analog read of pin A0 to create a different sequence each time.
// The game uses a boolean variable to check if the user has lost or won.
// The game uses a for loop to create the sequence and check the user's response.
// The game uses a while loop to check for button presses and debounce the buttons.
// The game uses a function to create the win sequence and another function to create the lose sequence.
// The game uses a function to check for button presses and debounce the buttons.
// The game uses a function to detect which button is pressed.

int LEDPins[4] = {2, 3, 4, 5};
int buttonPins[4] = {8, 9, 10, 11};
int LEDSequence[32];

void setup() {
  Serial.begin(9600);
  // Set our input and output pins
  for (int i = 0; i < 4; i++) {
    pinMode(LEDPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(A0));
}

void loop() {
  // Create bool for failure
  bool lose = false;

  // Create random sequence for lights
  Serial.println("The sequence is: ");
  for (int i = 0; i < 32; i++) { // Generate sequence for all levels
    LEDSequence[i] = random(4);
    Serial.print(LEDSequence[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Game starts here
  for (int level = 1; level <= 32; level++) {
    // Show the loop
    for (int i = 0; i < level; i++) {
      digitalWrite(LEDPins[LEDSequence[i]], HIGH);
      delay(750);
      digitalWrite(LEDPins[LEDSequence[i]], LOW); // Turn off LED
    }
    delay(1000);

    // Wait for a response loop
    for (int i = 0; i < level; i++) {
      int button = -1;
      while (button < 0) {
        button = buttonPressed();
      }

      // Telling user which button is pressed
      digitalWrite(LEDPins[button], HIGH);
      delay(250);
      digitalWrite(LEDPins[button], LOW);
      delay(250);

      // Check against sequence
      if (LEDSequence[i] != button) {
        lose = true;
        break;
      }
    }

    // Win or lose loop
    if (lose) {
      loseSeq();
      break;
    } else if (!lose && level == 32) {
      winSeq();
    }
  }
}

// Sequence for win
void winSeq() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(LEDPins[j], HIGH);
    }
    delay(500);
    for (int j = 0; j < 4; j++) {
      digitalWrite(LEDPins[j], LOW);
    }
    delay(500);
  }
}

// Sequence for lose
void loseSeq() {
  for (int j = 0; j < 4; j++) {
    digitalWrite(LEDPins[j], HIGH);
  }
  delay(500);
  for (int j = 0; j < 4; j++) {
    digitalWrite(LEDPins[j], LOW);
  }
}

// Check for debounce
bool isPressed(int buttonChk) {
  bool pressed = false;
  if (digitalRead(buttonPins[buttonChk]) == LOW) {
    delay(10);
    while (digitalRead(buttonPins[buttonChk]) == LOW) {}
    delay(10);
    pressed = true;
  }
  return pressed;
}

// Detect which button is pressed
int buttonPressed() {
  int buttonNum = -1;
  for (int j = 0; j < 4; j++) {
    if (isPressed(j)) {
      buttonNum = j;
      break; // Exit loop once a button is detected
    }
  }
  return buttonNum;
}