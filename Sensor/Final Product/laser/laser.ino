#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

RTC_DATA_ATTR unsigned int time_to_midnight;
int one_sec  = 1000000; //micro second to 1 one second

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip

WiFiClient espClient;
PubSubClient client(espClient);

// ved resistor: grøn = ground, hvid = 0, brun = 5v 
// ved laser: orange = ground, hvid = 5v

int ldr = 2; //analog pin to which LDR is connected
int ldr_value = 0; //variable to store LDR values
int old_ldr = 0;

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

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.connect("ESP32Laser");
  Serial.begin(9600);
  pinMode(ldr,INPUT);
}

void loop() {
  time_to_midnight = 86400 - (getTime() % 86400);
  if (time_to_midnight=0){
    client.publish("sensor/alive", "Laser");
  }
  ldr_value = analogRead(ldr); //reads the LDR values
  delay(100); //waits
  if (abs(ldr_value - old_ldr) >= 500 && ldr_value < 1000) {
    client.publish("sensor/door","Person gik igennem");
  }
  old_ldr = ldr_value;
}