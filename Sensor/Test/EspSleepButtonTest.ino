#include <WiFi.h>
#include <PubSubClient.h>

#define INTERRUPT_PIN 2 //green button (yellow wire)

const char* ssid = "P1"; //wifi ssid
const char* password = "password1234"; //wifi password
const char* mqtt_server = "192.168.1.149"; //mqtt server ip

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

void callback(char* topic, byte* payload, unsigned int length) {} //end callback

void setup() {
  esp_deep_sleep_enable_gpio_wakeup(1 << INTERRUPT_PIN, ESP_GPIO_WAKEUP_GPIO_LOW); //wake up from deep sleep
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.connect("ESP32Button");
  client.publish("sensor/button", "Green Button Pressed");
  esp_deep_sleep_start(); //go to deep sleep
}

void loop() {
}
