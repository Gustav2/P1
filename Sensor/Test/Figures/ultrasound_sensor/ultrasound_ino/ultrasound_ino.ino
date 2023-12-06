#include <Ultrasonic.h>

//Vcc wire 5v
//Gnd wire ground
//Echo wire on pin 8
//Trig wire on pin 9
Ultrasonic ultrasonic1(9, 8);	// An ultrasonic sensor HC-04
int BUTTON_PIN1 = 2;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN1, INPUT);
}

void loop() {
  Serial.println(ultrasonic1.read()); // Prints the distance on the default unit (centimeters)

  if (digitalRead(BUTTON_PIN1)==LOW) {
    Serial.println("button pressed");
  }

  delay(50);
}