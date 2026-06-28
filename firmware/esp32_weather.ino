#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <time.h>

#define DHTPIN 4
#define DHTTYPE DHT22

// =========================
// HY-SRF05
// =========================
#define TRIG_PIN 5
#define ECHO_PIN 18

DHT dht(DHTPIN, DHTTYPE);

// =========================
// WIFI
// =========================
const char* ssid = "KODOKATRET-2.4G";
const char* password = "DC8814XH";

// =========================
// HIVEMQ
// =========================
const char* mqtt_server =
"df9575cf81dd4ea39cc9fe88f106c3ab.s1.eu.hivemq.cloud";

const int mqtt_port = 8883;

const char* mqtt_user = "syopijh";
const char* mqtt_pass = "Treasure12pjh";

WiFiClientSecure espClient;
PubSubClient client(espClient);

const String deviceID = "ESP32-01";

// =========================
// NTP TIME
// =========================
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;      // WIB (UTC+7)
const int daylightOffset_sec = 0;

// =========================
// WIFI CONNECT
// =========================
void setupWiFi() {

  Serial.println("");
  Serial.println("Connecting WiFi...");
  Serial.print("SSID : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int counter = 0;

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

    counter++;

    if(counter > 40){
      Serial.println("");
      Serial.println("WiFi Connection Failed!");
      return;
    }
  }

  Serial.println("");
  Serial.println("================================");
  Serial.println("WiFi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println("================================");
}

// =========================
// MQTT CONNECT
// =========================
void reconnect() {

  while (!client.connected()) {

    Serial.println("Connecting MQTT...");

    String clientId = "ESP32Weather-";
    clientId += String(random(0xffff), HEX);

    if (
      client.connect(
        clientId.c_str(),
        mqtt_user,
        mqtt_pass
      )
    ) {

      Serial.println("MQTT Connected!");

    } else {

      Serial.print("MQTT Failed. RC = ");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

// =========================
// READ DISTANCE
// =========================
long readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if(duration == 0){
    return -1;
  }

  long distance = duration * 0.0343 / 2;

  return distance;
}

// =========================
// SETUP
// =========================
void setup() {

  Serial.begin(115200);

  delay(2000);

  Serial.println("");
  Serial.println("================================");
  Serial.println("SMART WEATHER START");
  Serial.println("================================");

  dht.begin();
  Serial.println("DHT22 Initialized");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("HY-SRF05 Initialized");

  setupWiFi();

  configTime(
  gmtOffset_sec,
  daylightOffset_sec,
  ntpServer
);

Serial.println("Waiting NTP Time...");

struct tm timeinfo;

while (!getLocalTime(&timeinfo)) {
  Serial.print(".");
  delay(500);
}

Serial.println("");
Serial.println("NTP Time Synced!");

  espClient.setInsecure();

  client.setServer(
    mqtt_server,
    mqtt_port
  );

  Serial.println("MQTT Server Configured");
}

// =========================
// LOOP
// =========================
void loop() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi Lost. Reconnecting...");
    setupWiFi();
  }

  if (!client.connected()) {

    reconnect();
  }

  client.loop();

  float temperature =
  dht.readTemperature();

  float humidity =
  dht.readHumidity();

  long distance =
  readDistance();

  String objectStatus;

if(distance == -1){

  objectStatus = "No Object";

}
else if(distance <= 20){

  objectStatus = "Very Close";

}
else if(distance <= 50){

  objectStatus = "Nearby";

}
else{

  objectStatus = "Safe";

}

struct tm timeinfo;

String timestamp = "Unknown";

if (getLocalTime(&timeinfo)) {

  char buffer[25];

  strftime(
    buffer,
    sizeof(buffer),
    "%Y-%m-%d %H:%M:%S",
    &timeinfo
  );

  timestamp = String(buffer);

}

  if (
    isnan(temperature) ||
    isnan(humidity)
  ) {

    Serial.println("Failed to read DHT22");
    delay(2000);
    return;
  }

  // ENCRYPTION (+10)
  float encryptedTemp =
  temperature + 10;

  float encryptedHum =
  humidity + 10;

  long encryptedDistance =
  distance + 10;


String payload =
"{\"device\":\"" + deviceID +
"\",\"time\":\"" + String(timestamp) + "\"" +
",\"temperature\":" + String(encryptedTemp,1) +
",\"humidity\":" + String(encryptedHum,1) +
",\"distance\":" + String(encryptedDistance) +
",\"status\":\"" + objectStatus +
"\"}";
  
  
  Serial.println("--------------------------------");
  Serial.print("Temp : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Hum  : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Distance : ");
Serial.print(distance);
Serial.println(" cm");

Serial.print("Status : ");
Serial.println(objectStatus);

Serial.print("Time : ");
Serial.println(timestamp);

Serial.println("Payload :");
Serial.println(payload);

 if(client.publish(
    "weather/data",
    payload.c_str()
)){
    Serial.println("Published to MQTT");
}
else{
    Serial.println("Failed Publish");
}

  delay(5000);
}