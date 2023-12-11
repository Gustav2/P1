//YF‐ S201 Water Flow Sensor
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0,l_minute;
unsigned char flowsensor = 9; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
float lastvol = 0.0;

const char* ssid = "P1";//put your wifi ssid here
const char* password = "password1234";//put your wifi password here.
const char* mqtt_server = "192.168.1.149";
const char* ntpServer = "1.dk.pool.ntp.org"; //NTP server

WiFiClient espClient;
PubSubClient client(espClient);

RTC_DATA_ATTR unsigned int time_to_midnight;
int one_sec  = 1000000; //micro second to 1 one second
int previousState = -1;

void setup_wifi() { //Connect to wifi. While loop breaks when connected.
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED);
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  time(&now);
  return now;
}

void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   setup_wifi();
   client.setServer(mqtt_server, 1883);
   client.connect("ESP32Flow");
   Serial.begin(115200);
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
   currentTime = millis();
   cloopTime = currentTime;
   
   configTime(0, 0, ntpServer);
   time_to_midnight = 86400 - (getTime() % 86400);
}
void loop ()
{
    int status;
  time_to_midnight = 86400 - (getTime() % 86400);
  if (time_to_midnight == 0) {
    client.publish("sensor/alive", "ESP32Flow");
  }
  
   currentTime = millis();
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0) {
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      l_minute = l_minute/60;
      vol = vol +l_minute;
      flow_frequency = 0; // Reset Counter

      
    }
    else if (vol>lastvol){
      lastvol=vol;
      Serial.print(vol);
      //char msg_out[1];
      //dtostrf(vol,0,1,msg_out);
      //client.publish("sensor/flowTotal", msg_out);
      vol=0;
      lastvol=0;
    }
   }
}