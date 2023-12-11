const int senderPin = 2;  // Tilslut senderen til pin 2
const int receiverPin = 3;  // Tilslut modtageren til pin 3

void setup() {
    Serial.begin(115200);
    pinMode(senderPin, OUTPUT);
    pinMode(receiverPin, INPUT);
}

void loop() {
    // Aktiver senderen
    digitalWrite(senderPin, HIGH);
    delayMicroseconds(10);  // Vent i en kort periode

    // Læs værdien fra modtageren 
    int receiverValue = digitalRead(receiverPin);

    // Udskriv status
    if (receiverValue == HIGH) {
        Serial.println("Forbindelse oprettet");
    } else {
        Serial.println("Forbindelse brudt");
    }

    // Deaktiver senderen
    digitalWrite(senderPin, LOW);

    // Vent et kort stykke tid før næste måling
    delay(100);
}
