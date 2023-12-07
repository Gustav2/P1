#include <Arduino.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

//Red wire 3.3v
//Black wire ground
//Yellow wire on pin 9 (SCL)
//White wire on pin 8 (SDA)

SensirionI2CSht4x sht4x;
    float temperature;
    float humidity;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    sht4x.begin(Wire);

}

void loop() {
sht4x.measureHighPrecision(temperature, humidity);
Serial.println(temperature);
delay(1000);

  
}