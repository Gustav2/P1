#include <WiFi.h>
#include <PubSubClient.h>

//Red wire 3.3v
//Black wire ground
//Yellow wire on int BUTTON1_PIN
//White wire on int BUTTON2_PIN

int BUTTON1_PIN = 2; //Green button
int BUTTON2_PIN = 3; //Red button

// Update these with values suitable for your network.
const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";
//const char* mqtt_server = "iot.eclipse.org";

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
  pinMode(BUTTON1_PIN,INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int status;
  //send message if button pressed
  if (digitalRead(BUTTON1_PIN)==LOW && digitalRead(BUTTON2_PIN)==HIGH) 
  {;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    //publish sensor data to MQTT broker
    client.publish("sensor/button", "Green Button Pressed");
       }
  if (digitalRead(BUTTON2_PIN)==LOW && digitalRead(BUTTON1_PIN)==HIGH) 
  {;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    //publish sensor data to MQTT broker
    client.publish("sensor/button", "Red Button Pressed");
       }
  if (digitalRead(BUTTON1_PIN)==LOW && digitalRead(BUTTON2_PIN)==LOW)
  {;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    //publish sensor data to MQTT broker
    client.publish("sensor/button", "Both Buttons Pressed");
       }
}
