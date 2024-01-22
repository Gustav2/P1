#include <PubSubClient.h>
#include <WiFi.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>
#include <string>

//TempHumidity:
//VCC on 3.3v
//Ground on ground
//SCL on pin 9
//SDA on pin 8

const char* ssid = "P1";                      //wifi ssid
const char* password = "password1234";        //wifi password
const char* mqtt_server = "192.168.1.149";    //mqtt server ip
const int mqtt_port = 1883;                   //mqtt server port
const char* UID = "ESP32Temp/Humidity";       //UID
const char* topic1 = "sensor/Temp";           //topic for temperature
const char* topic2 = "sensor/Humidity";       //topic for humidity
const int time_to_wakeup = 900;               //in seconds

WiFiClient espClient;
PubSubClient client(espClient);
SensirionI2CSht4x sht4x;

void initialize() {
  Serial.begin(9600);
  Serial.println("Begyndt");
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
    esp_sleep_enable_timer_wakeup(10000000);
    Wire.begin();
    sht4x.begin(Wire);
    initialize();  
    Serial.println("Hej");
    float temperature;
    float humidity;
    sht4x.measureHighPrecision(temperature, humidity);
    char msg_out1[6];
    char msg_out2[6];
    dtostrf(temperature,0,2,msg_out1);
    dtostrf(humidity,0,2,msg_out2);
    client.publish(topic1, msg_out1);
    client.publish(topic2, msg_out2);
    delay(50);
    esp_deep_sleep_start();
}

void loop() {
}
