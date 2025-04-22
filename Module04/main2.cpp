#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Uus";
const char* password = "iotempire";

const char* mqtt_server = "192.168.14.1";  // Mosquitto brokeri IP

WiFiClient espClient;
PubSubClient client(espClient);

#define TRIG_PIN 5
#define ECHO_PIN 18

long duration;
float distance;

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void setup_mqtt() {
  client.setServer(mqtt_server, 1883);  // Sea brokeri IP ja port
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Ühenda WiFi-ga
  setup_wifi();
  
  // Ühenda MQTT serveriga
  setup_mqtt();
  
  // Ühenda brokeriga
  if (client.connect("ESP32Sensor")) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Failed to connect to MQTT broker");
  }
}

void loop() {
  // Ultraheli mõõtmine
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2; // cm

  // Saada MQTT kaudu
  char msg[10];
  dtostrf(distance, 4, 2, msg);
  if (client.connected()) {
    client.publish("door/distance", msg);  // Saada kauguse väärtus "door/presence" teemal
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  delay(2000);  // Oota 2 sekundit enne järgmise mõõtmise tegemist
}