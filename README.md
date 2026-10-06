# 🌳 Sistem Manajemen Hutan

Program sederhana berbasis **C++** untuk mengelola data pohon di sebuah hutan. Program ini mendukung operasi CRUD (Create, Read, Update, Delete), penandaan status kesehatan pohon, perhitungan statistik, serta penyimpanan data ke file secara otomatis.


## Daftar Isi

- [Fitur](#fitur)
- [Struktur Data](#struktur-data)
- [Menu Program](#menu-program)
- [Format Penyimpanan File](#format-penyimpanan-file)
- [Validasi Input](#validasi-input)
- [Cara Kompilasi dan Menjalankan](#cara-kompilasi-dan-menjalankan)
- [Catatan](#catatan)


## Fitur

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


## Struktur Data

Setiap pohon direpresentasikan dalam `struct Pohon` dengan atribut berikut:
| Field | Tipe | Keterangan |
|-------|------|------------|
| `kode` | string | Kode unik pohon |
| `nama` | string | Nama pohon |
| `famili` | string | Famili pohon |
| `lokasi` | string | Lokasi penanaman |
| `tahun_tanam` | int | 1000–2024 |
| `tinggi` | double | 0.1–150 m |
| `diameter` | double | 0.1–1000 cm |
| `status` | bool | `true` = Sehat |


## Menu Program
<img width="301" height="311" alt="image" src="https://github.com/user-attachments/assets/9f29b688-f952-408a-be1a-1d7cf9553f08" />

## Format Penyimpanan File

Data disimpan dalam file data_kehutanan.txt dengan format CSV, akan tersimpan dengan format `data_kehutanan.txt`.

```cpp
kode,nama,famili,lokasi,tahun_tanam,tinggi,diameter,status
P001,Mahoni,Meliaceae,Taman Kota,2010,12.5,45.0,1
```
Status: `1` = Sehat, `0` = Sakit


## Validasi Input

Program melakukan validasi pada saat **tambah** dan **edit** data:

| No | Field | Aturan Validasi |
|----|-------|-----------------|
| 1 | Tahun Tanam | 1000 – 2024 |
| 2 | Tinggi | 0.1 – 150 meter |
| 3 | Diameter | 0.1 – 1000 cm |
| 4 | Kode Pohon | Harus unik (tidak boleh duplikat) |

## Cara Kompilasi dan Menjalankan
1. instal Compiler C++ (g++, clang++, atau MSVC)
2. Terminal / Command Prompt

Compile
```cpp
g++ -o manajemen_hutan main.cpp
```

Jalankan:  

Linux / macOS:
```cpp
./manajemen_hutan
```

Windows
```cpp
manajemen_hutan.exe
```


## Catatan

- Data **disimpan otomatis** saat pengguna memilih menu keluar (`0`).
- Status default pohon baru adalah **Sehat**.
- Program menggunakan `try-catch` saat membaca file untuk menangani data yang korup/tidak valid.
- File data (`data_kehutanan.txt`) akan dibuat otomatis di direktori yang sama dengan executable.
