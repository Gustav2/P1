#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

//5v på det ene ben af force sensor.
//fsrPin på det andet ben.
//Ground pin på en 10k ohm resistor.

int fsrPin = 9;         // FSR og 10K pulldown er forbundet til a0
int fsrReading;         // Analog læsning fra FSR resistordeler
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
  time_to_midnight = 86400 - (getTime() % 86400);
}

void loop() {
  int status;
  fsrReading = analogRead(fsrPin);
  time_to_midnight = 86400 - (getTime() % 86400);

  if (time_to_midnight == 0) {
    client.publish("sensor/alive", "UID(123)");
  }

  if (fsrReading < 250 && previousState != 0) {
    client.publish("sensor/force", "Køleskab Åben");
    previousState = 0;
  } else if (fsrReading > 250 && previousState != 1) {
    client.publish("sensor/force", "Køleskab Lukket");
    previousState = 1;
  }
}
