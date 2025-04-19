#include <Arduino.h> // Include Arduino functions

int delayTime = 90;

void setup() {
  for (int i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Forward loop
  for (int i = 2; i < 8; i++) {
    digitalWrite(i, HIGH);
    if (i == 2) {
      digitalWrite(7, LOW);
    } else {
      digitalWrite((i - 1), LOW);
    }
    delay(delayTime);
  }

  // Backward loop
  for (int i = 7; i >= 2; i--) {
    digitalWrite(i, HIGH);
    digitalWrite((i - 1), LOW); // Fix: Avoid accessing pin 8
    delay(delayTime);
  }
}