#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define SS_PIN  10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "Uus";
const char* password = "iotempire";
const char* mqtt_server = "192.168.14.1";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("WemosD1Mini")) {
      client.subscribe("rfid/logs");
    } else {
      delay(5000);
    }
  }
}

void sendLogToMQTT(String message) {
  if (client.connected()) {
    client.publish("rfid/logs", message.c_str());
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  SPI.begin();
  mfrc522.PCD_Init();
  sendLogToMQTT("MFRC522 Initialized");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String tagUID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        tagUID += String(mfrc522.uid.uidByte[i], HEX);
      }
      tagUID.toUpperCase();

      sendLogToMQTT("Card UID: " + tagUID);
      if (client.connected()) {
        client.publish("rfid/tag", tagUID.c_str());
      }
      
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }
}
