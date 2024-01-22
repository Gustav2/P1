#include <WiFi.h>
#include <PubSubClient.h>

//LDR:
//5v on one pin of the Light Dependent Resistor.
//Analogue_Pin on the other pin, between 10k ohm resistor and pin.
//Ground pin on a 10k ohm resistor.

//Laser:
//5v on 5v
//Ground pin on ground

int Analogue_Pin = 2;          // LDR and 10K pulldown are connected to pin 2
int Analogue_Reading;          // Analogue reading from LDR
int Threshold = 3300;          // Light threshold from opening refrigerator.
int Previous_State;            // Initialise the previous state

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "ESP32Laser";              //UID
const char* topic = "sensor/Fridge";          //topic

WiFiClient espClient;
PubSubClient client(espClient);

void initialize() {
  Serial.begin(9600);
  while (!client.connected()) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      
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
  Serial.println(Analogue_Reading);
  if (Analogue_Reading >= Threshold && Previous_State != 0) {
    Previous_State = 0;
  } else if (Analogue_Reading < Threshold && Previous_State != 1) {
    client.publish(topic, "Fridge ");
    Previous_State = 1;
  }
}