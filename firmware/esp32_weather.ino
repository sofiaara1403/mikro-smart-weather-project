#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

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

  setupWiFi();

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

  String payload =
    "{\"temperature\":"
    + String(encryptedTemp)
    + ",\"humidity\":"
    + String(encryptedHum)
    + "}";

  Serial.println("--------------------------------");
  Serial.print("Temp : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Hum  : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Payload : ");
  Serial.println(payload);

  client.publish(
    "weather/data",
    payload.c_str()
  );

  Serial.println("Published to MQTT");

  delay(5000);
}