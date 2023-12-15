#include <WiFi.h>
#include <PubSubClient.h>

//5v on one leg of the Force Sensitive Resistor
//Analogue_Pin on the other pin, between 10k ohm resistor and pin.
//Ground pin on a 10k ohm resistor.

int fsrPin = 0;         // FSR and 10k pulldown connected to pin 0
int fsrReading;         // Analogue reading from FSR
int previousState = -1; // Initialise previous state

// Update these with values suitable for your network.
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
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(void) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int status;
  fsrReading = analogRead(fsrPin);

  // Tjek om tilstanden har ændret sig fra forrige læsning
  if (fsrReading < 250 && previousState != 0) {
    Serial.println("Køleskab Åben");
    client.publish("sensor/force", "Køleskab Åben");
    previousState = 0;
  } else if (fsrReading > 250 && previousState != 1) {
    Serial.println("Køleskab lukket");
    client.publish("sensor/force", "Køleskab lukket");
    previousState = 1;
  }
  
  delay(2000);
}
