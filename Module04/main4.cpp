#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RELAY_PIN D1

// ⚙️ WiFi seaded
const char* ssid = "Uus";
const char* password = "iotempire";

// 🛰️ MQTT seaded
const char* mqtt_server = "192.168.14.1";  // näiteks "192.168.1.10"
const char* mqtt_topic = "door/open";

// 📡 WiFi & MQTT kliendid
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Ühendan WiFi-ga: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("✅ WiFi ühendatud");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Loeme sõnumi stringiks
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim();

  Serial.print("MQTT sõnum teemal [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Kontrollime kas "on" või "off"
  if (message == "on") {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("🔓 Uks avatud");
  } else if (message == "off") {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("🔒 Uks suletud");
  } else {
    Serial.println("❓ Tundmatu käsk");
  }
}

void reconnect() {
  // Proovime uuesti ühenduda kui vaja
  while (!client.connected()) {
    Serial.print("Ühendun MQTT serveriga...");
    if (client.connect("doorClient")) {
      Serial.println("✅ Ühendatud");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("❌ Ei saanud ühendust. Kood=");
      Serial.print(client.state());
      Serial.println(" Proovin 5s pärast uuesti...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
