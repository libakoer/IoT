#include <Arduino.h>

#define RELAY_PIN D1

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
  Serial.begin(115200);
  Serial.println("Connected to lock mechanism. Type on or off");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "on") {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("🔓 Open");
    } else if (command == "off") {
      digitalWrite(RELAY_PIN, LOW); 
      Serial.println("🔒 Closed");
    } else {
      Serial.println("❓ Unknown command. Use 'on' or 'off'");
    }
  }
}


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

