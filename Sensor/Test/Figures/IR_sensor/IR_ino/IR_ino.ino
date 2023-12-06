int BUTTON_PIN1 = 2;
#define sensor 0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(115200); // start the serial port
  pinMode(BUTTON_PIN1, INPUT);
}

void loop() {
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  
  Serial.println(distance);   // print the distance
  
  if (digitalRead(BUTTON_PIN1)==LOW) {
    Serial.println("button pressed");
  }
  delay(50);
}