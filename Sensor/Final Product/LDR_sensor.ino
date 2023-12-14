#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

//5v på det ene ben af LDR sensor.
//LDR_Pin på det andet ben, mellem 10k ohm resistor og benet.
//Ground pin på en 10k ohm resistor.

int LDR_Pin = 2;         // LDR og 10K pulldown er forbundet til 2
int LDR_Reading;         // Analog læsning fra LDR
int LDR_Threshold = 1400; // Lys grænse for åbning af køleskab
int Previous_State = -1; // Initialiser den forrige tilstand

RTC_DATA_ATTR unsigned int time_to_midnight;
int one_sec  = 1000000; //micro second to 1 one second

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip
const char* ntpServer = "1.dk.pool.ntp.org"; //NTP server
const char* UID = "ESP32LDR"; //UID

WiFiClient espClient;
PubSubClient client(espClient);

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  getLocalTime(&timeinfo);    
  time(&now);
  return now;
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
}

void setup_mqtt() {
  client.setServer(mqtt_server, 1883);
  client.connect(UID); //set the UID.
  while (!client.connected());
}

void setup_ntp() {  
  configTime(0, 0, ntpServer);
  delay(50);
}

void initialize() {
  setup_wifi();
  setup_mqtt();
  setup_ntp();
}

void setup() {    
  initialize();
}

void loop() {
  unsigned long getTime();
  unsigned long now;
  if (WiFi.status() != WL_CONNECTED || !client.connected() || !(now = getTime())) {
    initialize();
    delay(50);
  }

  delay(150);
  LDR_Reading = analogRead(LDR_Pin);
  time_to_midnight = 86400 - (getTime() % 86400);
  delay(50);
  if (time_to_midnight == 0) {
    client.publish("sensor/alive", UID);
  }
  if (LDR_Reading >= LDR_Threshold && Previous_State != 0) {
    client.publish("sensor/LDR", "Fridge_Open");
    Previous_State = 0;
  } else if (LDR_Reading < LDR_Threshold && Previous_State != 1) {
    client.publish("sensor/LDR", "Fridge_Closed");
    Previous_State = 1;
  }
}
