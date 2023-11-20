#include <WiFi.h>
#include <PubSubClient.h>

#define INTERRUPT_PIN 2

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



void setup() {
  esp_deep_sleep_enable_gpio_wakeup(1 << INTERRUPT_PIN, ESP_GPIO_WAKEUP_GPIO_LOW);
  Serial.begin(115200);
  delay(2000);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
  client.publish("sensor/button", "Green Button Pressed");
  delay(5000);
  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("besked sendt, slukker igen");
}

void loop() {
}
