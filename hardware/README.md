Proyek: Smart Weather and Distance Monitoring Station

Deskripsi :
Proyek ini merupakan sistem pemantauan lingkungan berbasis Internet of Things (IoT) yang mengintegrasikan pemantauan kondisi cuaca dan deteksi jarak secara real-time. Sistem ini dirancang untuk menyediakan solusi digital yang efisien dalam memantau perubahan suhu, kelembapan, serta deteksi objek dalam jangkauan tertentu secara otomatis. Data yang dikumpulkan diproses oleh mikrokontroler dan dikirimkan ke platform cloud untuk analisis lebih lanjut dan pemantauan jarak jauh.  

Detail Komponen :
HardwareSistem ini terdiri dari beberapa komponen kunci yang bekerja secara sinergis:ESP32 D1 R32 (Mikrokontroler): Merupakan otak sistem yang berfungsi sebagai unit pemrosesan pusat. D1 R32 dipilih karena memiliki arsitektur dual-core yang tangguh dan form factor yang kompatibel dengan header Arduino, memudahkan integrasi perangkat keras. Mikrokontroler ini menangani seluruh instruksi, membaca sinyal dari sensor, serta mengelola konektivitas Wi-Fi untuk pengiriman data ke cloud.  

- Sensor DHT22 (Modul): Sensor digital terintegrasi yang berfungsi mengukur suhu dan kelembapan udara. Di dalamnya terdapat sensor kapasitif untuk kelembapan dan termistor untuk suhu. Keunggulan modul ini adalah kemudahannya dalam koneksi karena sudah dilengkapi PCB pendukung, sehingga hanya membutuhkan satu pin data digital untuk mengirimkan informasi lingkungan ke ESP32.  
- Sensor Ultrasonik HY-SRF05: Sensor pengukur jarak yang bekerja berdasarkan prinsip sonar. Alat ini memiliki dua transduser: Trigger untuk memancarkan gelombang ultrasonik (frekuensi 40kHz) dan Echo untuk menerima pantulannya. Sistem ini mengonversi durasi waktu tempuh gelombang menjadi satuan jarak yang presisi.  
- Kabel Jumper (Female-to-Female): Berfungsi sebagai jalur komunikasi elektrik antar komponen. Kabel ini menghubungkan pin input/output pada ESP32 dengan pin pada modul sensor untuk memastikan daya listrik dan sinyal data tersalurkan dengan stabil.  
Cara Kerja Sistem
Sistem bekerja melalui siklus pemrosesan data sebagai berikut:
1. Inisiasi Sensor: ESP32 memberikan instruksi periodik kepada kedua sensor untuk memulai pembacaan data.
2. Akuisisi Data: 
- Sensor DHT22 mendeteksi perubahan resistansi internal akibat kondisi udara dan mengirimkan nilai suhu serta kelembapan dalam bentuk sinyal digital. 
- Secara bersamaan, HY-SRF05 memancarkan gelombang ultrasonik ke arah objek. Ketika gelombang tersebut memantul kembali, sensor mengirimkan sinyal durasi pantulan kepada ESP32 untuk dihitung jarak objeknya.
3. Pemrosesan & Transmisi: ESP32 mengolah seluruh nilai data tersebut dan mengirimkannya ke platform cloud (seperti HiveMQ) melalui koneksi Wi-Fi internal, yang memungkinkan data dapat diakses melalui dasbor pengguna dari mana saja.  

Kegunaan ProyekProyek ini sangat fleksibel dan dapat diterapkan dalam berbagai skenario:
- Otomasi Rumah & Gudang: Membantu memantau kondisi suhu gudang penyimpanan barang sensitif sekaligus mendeteksi jika ada pergerakan objek atau stok barang yang berpindah di area tertentu secara otomatis.  
- Sistem Keamanan: Digunakan sebagai detektor keberadaan objek dalam jangkauan tertentu yang diintegrasikan dengan data lingkungan sekitar.  
- Efisiensi Operasional: Membantu pengguna mendapatkan informasi akurat mengenai lingkungan secara otomatis tanpa perlu melakukan pengecekan manual di lapangan, sehingga meminimalkan human error dalam pemantauan rutin.