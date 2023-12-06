// Sharp IR GP2Y0A41SK0F Distance Test
// http://www.electronoobs.com/eng_arduino_tut72.php
#include <Arduino.h>

#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

//Red wire 3.3v
//Black wire ground
//Yellow wire on int BUTTON1_PIN
//White wire on int BUTTON2_PIN

int BUTTON1_PIN = 2; //Green button
int BUTTON2_PIN = 3; //Red button

void setup() {
  Serial.begin(115200); // start the serial port
  pinMode(BUTTON1_PIN,INPUT);
}

void loop() {
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(50); // slow down serial port 
  
  Serial.println(distance);   // print the distance

  if (digitalRead(BUTTON1_PIN)==LOW) {
    Serial.println("Button Pressed");
    }
}
