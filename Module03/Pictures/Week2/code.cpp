#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi settings
const char* ssid = "Uus";
const char* password = "iotempire";

// MQTT settings
const char* mqtt_server = "192.168.14.1";  // Your OpenWRT router IP
const int mqtt_port = 1883;
const char* mqtt_topic = "FirstAidStation/Button";

WiFiClient espClient;
PubSubClient client(espClient);

const int buttonPin = D5;  // D5 on ESP8266, vastab GPIO14
int lastButtonState = HIGH;

void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.print("Connecting to WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("D1MiniClient")) {  // Unikaalne kliendi nimi
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Sisetõmbetakisti nupu jaoks
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int currentButtonState = digitalRead(buttonPin);
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == LOW) {
      client.publish(mqtt_topic, "Button Pressed");
      Serial.println("Button Pressed");
    } else {
      client.publish(mqtt_topic, "Button Released");
      Serial.println("Button Released");
    }
    lastButtonState = currentButtonState;
    delay(50);  // Deebounci viivitus
  }
}