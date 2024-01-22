#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

//Red wire 5v
//Black wire ground
//Yellow wire on #define SENSOR

#define SENSOR 9

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "ESP32Flow";               //UID
const char* topic1 = "sensor/FlowRate";      //topic for flow rate
const char* topic2 = "sensor/FlowTotal";     //topic for flow total

WiFiClient espClient;
PubSubClient client(espClient);

int Previous_State;

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 7.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void initialize() {
  while (!client.connected()) {
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(50); 
    }
    client.setServer(mqtt_server, mqtt_port);
    client.connect(UID);
    delay(50);
  }
}

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  initialize();
  pinMode(SENSOR, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
}

void loop() { 
  if (client.connected()) {
    client.loop();
  }
  delay(50);
  if (WiFi.status() != WL_CONNECTED || !client.connected()) {
    initialize();
  }
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate =  pulse1Sec / calibrationFactor;
    previousMillis = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    if (flowRate > 0 && Previous_State != 0) { 
      client.publish(topic1, "start");
      Previous_State = 0;
    } else if (flowRate == 0  && Previous_State != 1) {
      client.publish(topic1, "stop");
      char msg_out[10];
      dtostrf(totalMilliLitres,0,1,msg_out);
      client.publish(topic2, msg_out);
      totalMilliLitres = 0;
      Previous_State = 1;
    } 
  }
}
