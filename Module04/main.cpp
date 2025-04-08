#include <Arduino.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h> // ✅ ÕIGE ESP8266 jaoks
#include <PubSubClient.h>

// ---- WiFi ja MQTT konfiguratsioon ----
const char* ssid = "Uus";       // ⚡ Muuda oma WiFi nimeks
const char* password = "iotempire"; // ⚡ Muuda oma WiFi parooliks
const char* mqtt_server = "192.168.14.1";  // ⚡ Muuda oma MQTT brokeri IP-ks või kasuta "broker.hivemq.com"

#define ONE_WIRE_BUS D2  // ⚡ Dallas DS18B20 ühendatud D2 (GPIO4)

// MQTT kliendi seadistamine
WiFiClient espClient;
PubSubClient client(espClient);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---- WiFi ühendamine ----
void setup_wifi() {
  delay(10);
  Serial.println("WiFi ühendamine...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi ühendatud!");
}

// ---- MQTT ühendamine ----
void reconnect() {
  while (!client.connected()) {
    Serial.print("Ühendamine MQTT serveriga...");
    if (client.connect("ESP8266_Temperature_Sensor")) {
      Serial.println("Ühendatud!");
    } else {
      Serial.print("Ühendus ebaõnnestus, viga: ");
      Serial.print(client.state());
      Serial.println(" - Proovin uuesti 5 sek pärast.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
  sensors.begin(); // Alusta Dallas temperatuuri anduri tööd
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);  // Loeb esimest andurit

  if (temperature != DEVICE_DISCONNECTED_C) {
    Serial.print("Saadan temperatuuri: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString); // Float → String
    client.publish("home/sensor/temperature", tempString);
  } else {
    Serial.println("Andur ei vasta!");
  }

  delay(5000); // Saada uus väärtus iga 5 sekundi tagant
}
