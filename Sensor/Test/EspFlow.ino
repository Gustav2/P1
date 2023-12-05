#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

//Red wire 5v
//Black wire ground
//Yellow wire on #define SENSOR
#define SENSOR  9

const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";
const char* ntpServer = "1.dk.pool.ntp.org"; //NTP server

WiFiClient espClient;
PubSubClient client(espClient);

RTC_DATA_ATTR unsigned int time_to_midnight;
int one_sec  = 1000000; //micro second to 1 one second

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  time(&now);
  return now;
}

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.connect("ESP32Flow");
  pinMode(SENSOR, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

  configTime(0, 0, ntpServer);
  time_to_midnight = 86400 - (getTime() % 86400);
}

void loop()
{ int status;
  time_to_midnight = 86400 - (getTime() % 86400);
  Serial.println(time_to_midnight);
  if (time_to_midnight == 0) {
    client.publish("sensor/alive", "ESP32Flow");
  }

  client.loop();
    delay(2000);
    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      
      pulse1Sec = pulseCount;
      pulseCount = 0;
      flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
      previousMillis = millis();
      flowMilliLitres = (flowRate / 60) * 1000;

      totalMilliLitres += flowMilliLitres;
      if (flowRate > 0) { 
      char msg_out1[2];
      dtostrf(flowRate,0,2,msg_out1);
      client.publish("sensor/flowRate", msg_out1);
      char msg_out2[2];
      dtostrf(totalMilliLitres,0,2,msg_out2);
      client.publish("sensor/flowTotal", msg_out2);
      delay(50);
      } 
      
  }

}