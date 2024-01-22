#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "P1";                     //wifi ssid
const char* password = "password1234";       //wifi password
const char* mqtt_server = "192.168.1.149";   //mqtt server ip
const int mqtt_port = 1883;                  //mqtt server port
const char* UID = "<UID>";                   //UID
const char* topic = "sensor/<UID>";          //topic

WiFiClient espClient;
PubSubClient client(espClient);

void initialize() {
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
}

void loop() {
  if (client.connected()) {
    client.loop();
  }
  delay(50);
  if (WiFi.status() != WL_CONNECTED || !client.connected()) {
    initialize();
  }
  // Sensor code below
}
