#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

//5v på det ene ben af LDR sensor.
//LDR_Pin på det andet ben, mellem 10k ohm resistor og benet.
//Ground pin på en 10k ohm resistor.

int LDR_Pin = 2;         // LDR og 10K pulldown er forbundet til 2
int LDR_Reading;         // Analog læsning fra LDR
int previousState = -1; // Initialiser den forrige tilstand

RTC_DATA_ATTR unsigned int time_to_midnight;
int one_sec  = 1000000; //micro second to 1 one second

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip
const char* ntpServer = "1.dk.pool.ntp.org"; //NTP server

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
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

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.connect("x"); //set the UID.
  configTime(0, 0, ntpServer);
}

void loop() {
  LDR_Reading = analogRead(LDR_Pin);
  time_to_midnight = 86400 - (getTime() % 86400);

  if (time_to_midnight == 0) {
    client.publish("sensor/alive", "UID(123)");
  }

  if (LDR_Reading < 100 && previousState != 0) {
    client.publish("sensor/LDR", "Køleskab Åben");
    previousState = 0;
  } else if (LDR_Reading > 100 && previousState != 1) {
    client.publish("sensor/LDR", "Køleskab Lukket");
    previousState = 1;
  }
}
