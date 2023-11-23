#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
//#include <string>
#include <Ultrasonic.h>


const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";

Ultrasonic ultrasonic(9, 8);	// i format (trig, echo)

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

void callback(char* topic, byte* payload, unsigned int length) {} //end callback

void setup()
{
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(115200);
  while (!Serial) {
      delay(100);
  }
}

void loop() {
  int distance = ultrasonic.read();
  if (distance < 75) {
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    Serial.begin(115200);
    char msg_out1[2];
    dtostrf(distance,0,2,msg_out1);
    client.publish("sensor/ultraDistance", msg_out1);       
    }
  delay(100);
  }