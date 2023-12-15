#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

//LDR:
//5v på det ene ben af Light Sensitive Resistor.
//Analogue_Pin på det andet ben, mellem 10k ohm resistor og benet.
//Ground pin på en 10k ohm resistor.

//Laser:
//5v på 5v
//Ground pin på ground

int Analogue_Pin = 2;          // LDR og 10K pulldown er forbundet til pin 2
int Analogue_Reading;          // Analog læsning fra LDR
int Threshold = 1000;          // Lys grænse for åbning af køleskab
int Previous_State;            // Initialiser den forrige tilstand

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "ESP32Laser";              //UID
const char* topic = "sensor/Laser";          //topic

WiFiClient espClient;
PubSubClient client(espClient);

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

void setup() {    
  initialize();
  pinMode(Analogue_Pin,INPUT);
}

void loop() {
  if (client.connected()) {
    client.loop();
  }
  delay(50);
  if (WiFi.status() != WL_CONNECTED || !client.connected()) {
    initialize();
  }
  Analogue_Reading = analogRead(Analogue_Pin);
  if (Analogue_Reading >= Threshold && Previous_State != 0) {
    Previous_State = 0;
  } else if (Analogue_Reading < Threshold && Previous_State != 1) {
    client.publish(topic, "Person_entered");
    Previous_State = 1;
  }
}
