#include <Arduino.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

SensirionI2CSht4x sht4x;

const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  
} //end callback

void setup() {
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }
    Wire.begin();
    sht4x.begin(Wire);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("OsoyooCommand");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} //end reconnect()

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    delay(2000);
    float temperature;
    float humidity;
    sht4x.measureHighPrecision(temperature, humidity);
        {
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("Humidity:");
        Serial.println(humidity);
        char msg_out1[2];
        dtostrf(temperature,0,2,msg_out1);
        client.publish("sensor/temp", msg_out1);
        char msg_out2[2];
        dtostrf(humidity,0,2,msg_out2);
        client.publish("sensor/humidity", msg_out2);
    }
}
