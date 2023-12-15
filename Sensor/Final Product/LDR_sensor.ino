#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

//5v på det ene ben af LDR sensor.
//LDR_Pin på det andet ben, mellem 10k ohm resistor og benet.
//Ground pin på en 10k ohm resistor.

int LDR_Pin = 2;          // LDR og 10K pulldown er forbundet til 2
int LDR_Reading;          // Analog læsning fra LDR
int LDR_Threshold = 1400; // Lys grænse for åbning af køleskab
int Previous_State;       // Initialiser den forrige tilstand

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "ESP32LDR";                //UID
const char* topic = "sensor/LDR";            //topic

WiFiClient espClient;
PubSubClient client(espClient);

void initialize() {
  while (!client.connected()) {
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(50); 
    client.setServer(mqtt_server, mqtt_port);
    client.connect(UID);
    delay(50);
    }
  }
}

void setup() {    
  initialize();
}

void loop() {
  if (client.connected()) {
    client.loop();
  }
  delay(50);
  if (WiFi.status() != WL_CONNECTED || !client.connected()) {
    initialize();
  }
  LDR_Reading = analogRead(LDR_Pin);
  if (LDR_Reading >= LDR_Threshold && Previous_State != 0) {
    client.publish(topic, "Fridge_Open");
    Previous_State = 0;
  } else if (LDR_Reading < LDR_Threshold && Previous_State != 1) {
    client.publish(topic, "Fridge_Closed");
    Previous_State = 1;
  }
}
