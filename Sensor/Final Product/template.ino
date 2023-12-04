#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

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

  if (esp_sleep_get_wakeup_cause() == x) { //find the wake up cause and set as x and change the publish topic and message.
  client.publish("topic", "x");
  }

  if (esp_sleep_get_wakeup_cause() == 7) {
  client.publish("topic", "knap");
  }

  time_to_midnight = 86400 - (getTime() % 86400);
  //set a wake up reason based on sensor.
  esp_sleep_enable_timer_wakeup(time_to_midnight * one_sec);

  esp_deep_sleep_start();
}

void loop() {
}