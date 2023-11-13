#include <Arduino.h>
#include <Ultrasonic.h>

//Vcc wire 5v
//Gnd wire ground
//Echo wire on pin 8
//Trig wire on pin 9
Ultrasonic ultrasonic1(9, 8);	// An ultrasonic sensor HC-04


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Sensor 01: ");
  Serial.print(ultrasonic1.read()); // Prints the distance on the default unit (centimeters)
  Serial.println("cm");

  delay(1000);
}

