#include <Arduino.h>

int BUTTON1_PIN = 8; //Green button
int ldr = 2;                             // set input from PIR to pin 7
int ldr_value=0;                         // set variable digitalReadValue for store state of PIR input

void setup() {
  Serial.begin(115200);                         // start serial communication
  pinMode(ldr, INPUT);                   // set inputPin to INPUT
  pinMode(BUTTON1_PIN,INPUT);
}

void loop() {
  if (digitalRead(BUTTON1_PIN)==LOW) {
    Serial.println("Button Pressed");
    }
  delay(50);

  ldr_value = analogRead(ldr); //reads the LDR values
  Serial.println(ldr_value);


}