Temperatuurisensor:
'''#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "Shaco";
const char* password = "colonizer";

const char* mqtt_server = "192.168.43.4";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: " + WiFi.localIP().toString());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("TempSensorClient")) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  sensors.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("❌ Sensor disconnected!");
  } else {
    Serial.print("🌡️ Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");

    char tempStr[8];
    dtostrf(tempC, 1, 2, tempStr);

    client.publish("home/temperature", tempStr);
  }

  delay(5000);
'''
´´´ test ´´´
ja luku pool sellest.
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RELAY_PIN D1

const char* ssid = "Shaco";
const char* password = "colonizer";

const char* mqtt_server = "192.168.43.4";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim();

  Serial.print("Received from MQTT: ");
  Serial.println(message);

  if (message == "on") {
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    Serial.println("🔓 Open");
  } else if (message == "off") {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("🔒 Closed");
    delay(500);
  } else {
    Serial.println("❓ Unknown command. Use 'on' or 'off'");
  }
}

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("LockControllerClient")) {
      Serial.println("connected!");
      client.subscribe("home/lock");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start locked

  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println("Ready. Listening on topic: home/lock");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
