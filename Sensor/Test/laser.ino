#include <WiFi.h>
#include <PubSubClient.h>

#define INTERRUPT_PIN 2 //green button (yellow wire)

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip

WiFiClient espClient;
PubSubClient client(espClient);


//grøn = ground - hvid ved ldr = 0 - blå = 3v - hvid ved laser = 5 - orange = ground
int ldr = 0; //analog pin to which LDR is connected
int ldr_value = 0; //variable to store LDR values
int old_ldr = 0;

void setup() {
  Serial.begin(9600); //start the serial monitor

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.connect("ESP32Laser");

}

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

void callback(char* topic, byte* payload, unsigned int length) {} //end callback


void loop() {
  ldr_value = analogRead(ldr); //reads the LDR values

  delay(100); //wait

  if (abs(ldr_value - old_ldr) >=200 && ldr_value < 600) {
    client.publish("sensor/door","Person gik igennem");
    delay(3000); // 3 seconds of beeping to tell you the trip wire has been broken
  }
  old_ldr = ldr_value;

}