# 🌳 Sistem Manajemen Hutan

Program sederhana berbasis **C++** untuk mengelola data pohon di sebuah hutan. Program ini mendukung operasi CRUD (Create, Read, Update, Delete), penandaan status kesehatan pohon, perhitungan statistik, serta penyimpanan data ke file secara otomatis.

---

## 📋 Daftar Isi

- [Fitur](#-fitur)
- [Struktur Data](#-struktur-data)
- [Cara Kerja Program](#-cara-kerja-program)
- [Menu Program](#️-menu-program)
- [Format Penyimpanan File](#-format-penyimpanan-file)
- [Validasi Input](#-validasi-input)
- [Cara Kompilasi dan Menjalankan](#️-cara-kompilasi-dan-menjalankan)
- [Contoh Penggunaan](#-contoh-penggunaan)
- [Struktur Program](#️-struktur-program)
- [Catatan](#-catatan)
- [Author](#-author)
- [Lisensi](#-lisensi)

---

## ✨ Fitur

| No | Fitur | Deskripsi |
|----|-------|-----------|
| 1 | Tambah Data Pohon | Menambahkan data pohon baru ke dalam sistem |
| 2 | Tampilkan Semua Pohon | Menampilkan seluruh data pohon dalam bentuk tabel |
| 3 | Edit Data Pohon | Mengubah data pohon berdasarkan kode |
| 4 | Hapus Data Pohon | Menghapus data pohon dengan konfirmasi |
| 5 | Tandai Pohon Sakit | Mengubah status pohon menjadi sakit |
| 6 | Tandai Pohon Sehat | Mengubah status pohon menjadi sehat |
| 7 | Statistik Hutan | Menampilkan ringkasan statistik seluruh pohon |
| 8 | Simpan ke File | Menyimpan data ke file `data_kehutanan.txt` |
| 0 | Keluar | Menyimpan data otomatis lalu keluar dari program |

---

## 🧱 Struktur Data

Setiap pohon direpresentasikan dalam `struct Pohon` dengan atribut berikut:

```cpp
struct Pohon {
    string kode;         // Kode unik pohon
    string nama;         // Nama pohon
    string famili;       // Famili pohon
    string lokasi;       // Lokasi penanaman
    int tahun_tanam;     // Tahun tanam (1000–2024)
    double tinggi;       // Tinggi pohon dalam meter (0.1–150)
    double diameter;     // Diameter pohon dalam cm (0.1–1000)
    bool status;         // true = Sehat, false = Sakit
};
```
## 🚥 Menu Program
<img width="301" height="311" alt="image" src="https://github.com/user-attachments/assets/9f29b688-f952-408a-be1a-1d7cf9553f08" />
