<img width="1509" height="365" alt="WhatsApp Image 2026-06-28 at 20 51 14 (1)" src="https://github.com/user-attachments/assets/3b7130b0-21bc-4123-b220-75262a022fea" />

UAS Sistem Mikrokontroller 
Kelompok 3 :

Nama : BUDI AZHAR EKA ARDIANTO
Npm : 23552O11397

Nama : M Fikri Nasrulloh 
Npm :  23552011337

Nama : Sofia Risa Aulia
Npm : 23552011299

TIF 23 CNS A

# 🌤 Smart Weather & Object Monitoring

> IoT-Based Smart Weather Station with Real-Time Object Detection and Secure MQTT Communication
>
> ## 📌 Project Overview

Smart Weather & Object Monitoring merupakan sistem Internet of Things (IoT) yang dirancang untuk memantau kondisi lingkungan secara **real-time** sekaligus mendeteksi keberadaan objek di sekitar perangkat. Sistem ini menggunakan sensor **DHT22** untuk memperoleh data suhu dan kelembapan udara serta sensor ultrasonik **HY-SRF05** untuk mengukur jarak objek terhadap perangkat.

Data yang diperoleh diproses oleh **ESP32**, kemudian dilakukan proses **enkripsi sederhana** sebelum dikirim melalui protokol **MQTT over TLS** menuju **HiveMQ Cloud Broker**. Dashboard web kemudian menerima data tersebut menggunakan **WebSocket Secure (WSS)**, melakukan proses **dekripsi**, dan menampilkan hasil monitoring secara real-time dalam bentuk angka, grafik, maupun tabel log.

Selain berfungsi sebagai sistem monitoring cuaca sederhana, proyek ini juga mampu mendeteksi keberadaan objek di sekitar perangkat sehingga dapat dikembangkan menjadi sistem monitoring lingkungan maupun sistem keamanan berbasis IoT.

---

# 🎯 Objectives

Tujuan utama proyek ini adalah:

- Memonitor suhu lingkungan secara real-time
- Memonitor kelembapan udara
- Mendeteksi objek di sekitar perangkat
- Mengirim data sensor secara aman menggunakan MQTT TLS
- Menampilkan data pada dashboard web secara real-time
- Memberikan visualisasi data dalam bentuk grafik
- Menyimpan histori pembacaan sensor

---

