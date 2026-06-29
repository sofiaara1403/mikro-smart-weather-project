<img width="1509" height="365" alt="WhatsApp Image 2026-06-28 at 20 51 14 (1)" src="https://github.com/user-attachments/assets/3b7130b0-21bc-4123-b220-75262a022fea" />

UAS Sistem Mikrokontroller 

(Kelompok 3) 

Nama : BUDI AZHAR EKA ARDIANTO (23552O11397)

Nama : M Fikri Nasrulloh (23552011337)

Nama : Sofia Risa Aulia (23552011299)

TIF 23 CNS A

# 🌤 Smart Weather & Object Monitoring

> IoT-Based Smart Weather Station with Real-Time Object Detection and Secure MQTT Communication
>
> ## 📌 Project Overview

Smart Weather & Object Monitoring merupakan sistem Internet of Things (IoT) yang dirancang untuk memantau kondisi lingkungan secara **real-time** sekaligus mendeteksi keberadaan objek di sekitar perangkat. Sistem ini menggunakan sensor **DHT22** untuk memperoleh data suhu dan kelembapan udara serta sensor ultrasonik **HY-SRF05** untuk mengukur jarak objek terhadap perangkat.

Data yang diperoleh diproses oleh **ESP32**, kemudian dilakukan proses **enkripsi sederhana** sebelum dikirim melalui protokol **MQTT over TLS** menuju **HiveMQ Cloud Broker**. Dashboard web kemudian menerima data tersebut menggunakan **WebSocket Secure (WSS)**, melakukan proses **dekripsi**, dan menampilkan hasil monitoring secara real-time dalam bentuk angka, grafik, maupun tabel log.

Selain berfungsi sebagai sistem monitoring cuaca sederhana, proyek ini juga mampu mendeteksi keberadaan objek di sekitar perangkat sehingga dapat dikembangkan menjadi sistem monitoring lingkungan maupun sistem keamanan berbasis IoT.

---

# Objectives

Tujuan utama proyek ini adalah:

- Memonitor suhu lingkungan secara real-time
- Memonitor kelembapan udara
- Mendeteksi objek di sekitar perangkat
- Mengirim data sensor secara aman menggunakan MQTT TLS

---

# 🛠 Hardware Components

| Component | Function |
|------------|----------|
| ESP32 | Microcontroller |
| DHT22 | Temperature & Humidity Sensor |
| HY-SRF05 | Object Distance Sensor |
| Breadboard | Prototype Circuit |
| Jumper Wire | Electrical Connection |
| USB Cable | Power Supply |

📁 Detail hardware dapat dilihat pada folder:

hardware/

---

# CARA KERJA 

Cara kerja sistem dimulai ketika ESP32 terhubung ke WiFi, kemudian melakukan sinkronisasi waktu melalui NTP dan terhubung ke HiveMQ Cloud menggunakan protokol MQTT over TLS. Selanjutnya ESP32 membaca data dari sensor DHT22 (suhu dan kelembapan) serta HY-SRF05 (jarak objek), kemudian menentukan status objek berdasarkan jarak yang terdeteksi. Sebelum dikirim, data sensor disamarkan menggunakan metode offset +10 (obfuscation), lalu dikirim dalam format JSON ke HiveMQ Cloud melalui MQTT. Dashboard web menerima data tersebut secara real-time, melakukan proses decryption dengan mengurangi offset sebesar 10, kemudian menampilkan hasilnya berupa suhu, kelembapan, jarak, status objek, grafik, dan data log. Proses ini berlangsung otomatis setiap 5 detik sehingga informasi selalu diperbarui secara real-time.

---
# Features

✅ Real-Time Temperature Monitoring

✅ Real-Time Humidity Monitoring

✅ Object Distance Detection

✅ Object Status Detection

✅ Secure MQTT Communication (TLS)

✅ Simple Data Encryption

✅ Real-Time Dashboard

✅ Weather Chart

✅ Recent Data Log

✅ Device Information

✅ Last Update Time (NTP)

- Menampilkan data pada dashboard web secara real-time
- Memberikan visualisasi data dalam bentuk grafik
- Menyimpan histori pembacaan sensor

---

# 🌐 Software & Technologies

- Arduino IDE
- ESP32
- HTML5
- CSS3
- JavaScript
- Bootstrap 5
- Chart.js
- MQTT.js
- HiveMQ Cloud
- Git
- GitHub

---

# ⚙ System Architecture
<img width="210" height="330" alt="Untitled Diagram drawio (3)" src="https://github.com/user-attachments/assets/64f6b085-a6b0-4b68-804f-65b3e8500e67" />

---

# 🔄 System Workflow

1. ESP32 melakukan koneksi ke jaringan WiFi.
2. ESP32 membaca data dari sensor DHT22.
3. ESP32 membaca jarak menggunakan HY-SRF05.
4. Sistem menentukan status objek.
5. Data dienkripsi.
6. Payload JSON dibuat.
7. Payload dikirim ke HiveMQ Cloud menggunakan MQTT TLS.
8. Dashboard melakukan subscribe pada topic MQTT.
9. Dashboard menerima payload.
10. Dashboard melakukan dekripsi.
11. Dashboard memperbarui tampilan secara real-time.
12. Data ditampilkan pada grafik dan tabel log.

---

# 📦 JSON Payload

```json
{
    "device":"ESP32-01",
    "time":"2026-06-28 15:30:12",
    "temperature":37.8,
    "humidity":82.5,
    "distance":28,
    "status":"Very Close"
}

---

🔐 Security

Untuk meningkatkan keamanan komunikasi data, sistem menerapkan:

MQTT over TLS
WebSocket Secure (WSS)
Enkripsi data sebelum publish
Dekripsi data pada dashboard

Walaupun algoritma enkripsi yang digunakan masih sederhana untuk kebutuhan pembelajaran, arsitektur sistem telah dirancang agar mudah dikembangkan menggunakan algoritma enkripsi yang lebih kuat seperti AES.

---

📊 Dashboard

Dashboard menyediakan informasi:

Temperature
Humidity
Distance
Object Status
Device ID
Last Update
Encryption Status
Real-Time Chart
Recent Data Log

Dashboard menerima data secara langsung dari HiveMQ Cloud menggunakan MQTT WebSocket sehingga tidak memerlukan proses refresh halaman.

---

📁 Project Structure
mikro-smart-weather-project

├── arduino
│   └── smart_weather.ino
│
├── dashboard
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── hardware
│   ├── README.md
│   ├── wiring-diagram.png
│   └── photos
│
├── mqtt
│   ├── README.md
│   └── mqtt-flow.png
│
├── screenshots
│
├── docs
│
└── README.md

---

🚀 Installation
1 Clone Repository https://github.com/sofiaara1403/mikro-smart-weather-project.git

2 Upload Program
- Install Arduino IDE
- Install ESP32 Board
- Install Library
- DHT
- PubSubClient
- WiFi
- Upload program ke ESP32

3 Jalankan Dashboard
  dashboard/index.html

atau menggunakan
Live Server VS Code

---

👨‍💻 Team Members
| Name   | Responsibility                                               |
| ------ | ------------------------------------------------------------ |
| Syopii | ESP32 Programming, Dashboard Development, System Integration |
| Budi   | Hardware Assembly & Hardware Documentation                   |
| Fikri  | MQTT Configuration & MQTT Documentation                      |

---

📈 Future Development

Beberapa pengembangan yang dapat dilakukan:

Database Integration
Login Authentication
Mobile Application
Email Notification
Telegram Notification
ThingSpeak Integration
Firebase Integration
AI Weather Prediction
Machine Learning Analysis

---

