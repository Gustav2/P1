#include <Arduino.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

//Red wire 3.3v
//Black wire ground
//Yellow wire on pin 9 (SCL)
//White wire on pin 8 (SDA)
RTC_DATA_ATTR unsigned int bootcount=0;
int one_sec  = 1000000; //micro second to 1 one second
const char* uid = "ESP32Temp/Hum";
SensirionI2CSht4x sht4x;

const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

void setup() {
    esp_sleep_enable_timer_wakeup(60000000*30); // 60000000==1 min 
    bootcount++;
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    Wire.begin();
    sht4x.begin(Wire);
    client.connect(uid);
    if (bootcount==48) {
    client.publish("sensor/alive", uid);
    bootcount=0;
    }
    float temperature;
    float humidity;
    sht4x.measureHighPrecision(temperature, humidity);
        {
        char msg_out1[2];
        dtostrf(temperature,0,2,msg_out1);
        client.publish("sensor/temp", msg_out1);
        
        char msg_out2[2];
        dtostrf(humidity,0,2,msg_out2);
        client.publish("sensor/humidity", msg_out2);
    }
    delay(80);
    esp_deep_sleep_start();
}

void loop() {
  
}