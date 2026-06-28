# MQTT Communication

## Deskripsi

Pada proyek Smart Weather & Object Monitoring, komunikasi data dilakukan menggunakan protokol MQTT (Message Queuing Telemetry Transport).

MQTT dipilih karena memiliki ukuran paket yang kecil, ringan, cepat, serta sangat sesuai untuk perangkat Internet of Things (IoT).

---

# Broker MQTT

Broker yang digunakan adalah:

HiveMQ Cloud

Protocol

MQTT over TLS

Port

8883

Web Dashboard

WebSocket Secure (WSS)

Port

8884

---

# Konfigurasi

## ESP32

Host

df9575cf81dd4ea39cc9fe88f106c3ab.s1.eu.hivemq.cloud

Port

8883

Protocol

MQTT TLS

---

## Dashboard Website

Host

df9575cf81dd4ea39cc9fe88f106c3ab.s1.eu.hivemq.cloud

Protocol

WebSocket Secure

Port

8884

---

# Topic

```
weather/data
```

ESP32 melakukan publish ke topic tersebut.

Dashboard melakukan subscribe pada topic yang sama.

---

# Alur MQTT

```
ESP32

↓

Read Sensor

↓

Encrypt Data

↓

Publish

↓

HiveMQ Cloud

↓

Subscribe

↓

Dashboard

↓

Decrypt

↓

Display
```

---

# Payload

```json
{
  "device":"ESP32-01",
  "time":"2026-06-28 15:05:43",
  "temperature":37.9,
  "humidity":82.4,
  "distance":330,
  "status":"Safe"
}
```

---

# Enkripsi

Sebelum data dikirim, ESP32 melakukan proses enkripsi sederhana.

```
temperature + 10

humidity + 10

distance + 10
```

Contoh

```
Temperature asli

27.9

↓

Temperature terkirim

37.9
```

Dashboard melakukan proses dekripsi dengan cara:

```
37.9 - 10

=

27.9
```

---

# Mekanisme Publish

ESP32 mengirim data setiap:

```
5 detik
```

Menggunakan fungsi:

```
client.publish()
```

---

# Mekanisme Subscribe

Website menggunakan library MQTT.js.

```
client.subscribe("weather/data")
```

Ketika data diterima:

- Parsing JSON
- Dekripsi
- Update Dashboard
- Update Grafik
- Update Data Logging

---

# Keamanan

Implementasi keamanan yang digunakan meliputi:

- MQTT over TLS (SSL)
- Username Authentication
- Password Authentication
- Secure WebSocket (WSS)
- Enkripsi sederhana pada data sensor

---

# Keunggulan MQTT

- Ringan
- Latensi rendah
- Real-time
- Mendukung komunikasi Publish/Subscribe
- Efisien untuk perangkat IoT
- Mendukung komunikasi terenkripsi melalui TLS

---

# Implementasi pada Proyek

MQTT digunakan sebagai media komunikasi antara ESP32 dan Dashboard Website sehingga seluruh data sensor dapat dikirim secara real-time, aman, dan efisien tanpa memerlukan proses refresh halaman.