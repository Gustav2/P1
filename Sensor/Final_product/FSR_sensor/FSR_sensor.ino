#include <WiFi.h>
#include <PubSubClient.h>

//5v on one leg of the Force Sensitive Resistor.
//Analogue_Pin on the other pin, between 10k ohm resistor and pin.
//Ground pin on a 10k ohm resistor.

int Analogue_Pin = 2;          // FSR and 10k pulldown connected to pin 2
int Analogue_Reading;          // Analogue reading from FSR
int Threshold = 250;           // Light threshold from opening refrigerator.
int Previous_State;            // Initialise previous state

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "ESP32FSR";                //UID
const char* topic = "sensor/FSR";            //topic

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
    client.publish(topic, "Closed");
    Previous_State = 0;
  } else if (Analogue_Reading < Threshold && Previous_State != 1) {
    client.publish(topic, "Open");
    Previous_State = 1;
  }
}
