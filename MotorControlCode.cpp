include <Arduino.h>

int rightEnable = 3;
int forwardRight = 4;
int reverseRight = 5;
int leftEnable = 6;
int forwardLeft = 7;
int reverseLeft = 8;

void setup() {
  pinMode(rightEnable, OUTPUT);
  pinMode(forwardRight, OUTPUT);
  pinMode(reverseRight, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(forwardLeft, OUTPUT);
  pinMode(reverseLeft, OUTPUT);
}

void loop() {
  analogWrite(rightEnable, 255);
  analogWrite(leftEnable, 255);
  
  forward();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  rightTurn();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  reverse();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  leftTurn();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  spinRt();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  spinLt();
  delay(5000);  // Wait for 1000 millisecond(s)
  
  stp();
  delay(5000);  // Wait for 1000 millisecond(s)
  
}
void rightForward() {
  digitalWrite(reverseRight, LOW);
  digitalWrite(forwardRight, HIGH);
}

void rightReverse() {
  digitalWrite(reverseRight, HIGH);
  digitalWrite(forwardRight, LOW);
}
void leftForward() {

  digitalWrite(reverseLeft, LOW);
  digitalWrite(forwardLeft, HIGH);
}
void leftReverse() {
  digitalWrite(reverseLeft, HIGH);
  digitalWrite(forwardLeft, LOW);
}

void forward() {
  rightForward();
  leftForward();
}

void reverse() {
  rightReverse();
  leftReverse();
}

void rightTurn() {
  leftForward();
  analogWrite(rightEnable, 128);
  rightForward();
}

void leftTurn() {
  rightForward();
  analogWrite(leftEnable, 128);
  leftForward();
}

void spinRt() {
  rightReverse();
  leftForward();
}
void spinLt() {
  leftReverse();
  rightForward();
}

void stp(){
  analogWrite(rightEnable, 0);
  analogWrite(leftEnable, 0);
}