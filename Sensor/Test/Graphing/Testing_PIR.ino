#include <Arduino.h>

int BUTTON1_PIN = 2; //Green button
int inputPin = 7;                             // set input from PIR to pin 7
int digitalReadValue;                         // set variable digitalReadValue for store state of PIR input

void setup() {
  Serial.begin(115200);                         // start serial communication
  pinMode(inputPin, INPUT);                   // set inputPin to INPUT
  pinMode(BUTTON1_PIN,INPUT);
}

void loop() {
  digitalReadValue = digitalRead(inputPin);   // read digital pin 7 and store in digitalReadValue
  Serial.println(digitalReadValue);           // print digitalReadValue to serial monitor

  if (digitalRead(BUTTON1_PIN)==LOW) {
    Serial.println("Button Pressed");
    }
  delay(100);
}
