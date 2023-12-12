#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

//Red wire 5v
//Black wire ground
//Yellow wire on #define SENSOR
#define SENSOR  9

int previousState = -1;
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  pinMode(SENSOR, INPUT_PULLUP);
  Serial.begin(115200);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

}

void loop() { 
    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      
      pulse1Sec = pulseCount;
      pulseCount = 0;
      flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
      previousMillis = millis();
      flowMilliLitres = (flowRate / 60) * 1000;

      totalMilliLitres += flowMilliLitres;


      if (flowRate > 0 && previousState != 0) { 
        previousState = 0;
      }
      else if (flowRate == 0  && previousState != 1) {
         Serial.println(totalMilliLitres);
         totalMilliLitres = 0;
         previousState = 1;
      } 

    }}
