#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip

WiFiClient espClient;
PubSubClient client(espClient);

// ved resistor: grøn = ground, hvid = 0, brun = 5v 
// ved laser: orange = ground, hvid = 5v

int ldr = 0; //analog pin to which LDR is connected
int ldr_value = 0; //variable to store LDR values
int old_ldr = 0;

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.connect("ESP32Laser");
}

void loop() {
  ldr_value = analogRead(ldr); //reads the LDR values
  delay(100); //wait
  if (abs(ldr_value - old_ldr) >=200 && ldr_value < 600) {
    client.publish("sensor/door","Person gik igennem");
  }
  old_ldr = ldr_value;
}