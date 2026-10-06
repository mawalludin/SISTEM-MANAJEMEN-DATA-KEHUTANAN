#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Struktur data pohon
struct Pohon {
    string kode;
    string nama;
    string famili;
    string lokasi;
    int tahun_tanam;
    double tinggi; // dalam meter
    double diameter; // dalam cm
    bool status; // true = sehat, false = sakit
};

// Deklarasi fungsi
void tampilkanMenu();
void tambahPohon(vector<Pohon> &data);
void tampilkanSemuaPohon(const vector<Pohon> &data);
void editPohon(vector<Pohon> &data);
void hapusPohon(vector<Pohon> &data);
void tandaiSakit(vector<Pohon> &data);
void tandaiSehat(vector<Pohon> &data);
void hitungStatistik(const vector<Pohon> &data);
void simpanKeFile(const vector<Pohon> &data);
void bacaDataDariFile(vector<Pohon> &data);
int cariByKode(const vector<Pohon> &data, const string &kode);

int main() {
    vector<Pohon> dataPohon;
    int pilihan;
    
    // Baca data dari file saat program dimulai
    bacaDataDariFile(dataPohon);
    cout << "Data berhasil dimuat dari file.\n";
    
    do {
        tampilkanMenu();
        cout << "Pilih menu (0-8): ";
        cin >> pilihan;
        cin.ignore(); 
        
        switch(pilihan) {
            case 1:
                tambahPohon(dataPohon);
                break;
            case 2:
                tampilkanSemuaPohon(dataPohon);
                break;
            case 3:
                editPohon(dataPohon);
                break;
            case 4:
                hapusPohon(dataPohon);
                break;
            case 5:
                tandaiSakit(dataPohon);
                break;
            case 6:
                tandaiSehat(dataPohon);
                break;
            case 7:
                hitungStatistik(dataPohon);
                break;
            case 8:
                simpanKeFile(dataPohon);
                break;
            case 0:
                simpanKeFile(dataPohon); // Simpan otomatis saat keluar
                cout << "Data disimpan. Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
        cout << endl;
    } while(pilihan != 0);
    
    return 0;
}

// Tampilan Menu
void tampilkanMenu() {
    cout << "================================\n";
    cout << "      SISTEM MANAJEMEN HUTAN\n";
    cout << "================================\n";
    cout << "1. Tambah Data Pohon\n";
    cout << "2. Tampilkan Semua Pohon\n";
    cout << "3. Edit Data Pohon\n";
    cout << "4. Hapus Data Pohon\n";
    cout << "5. Tandai Pohon Sakit\n";
    cout << "6. Tandai Pohon Sehat\n";
    cout << "7. Statistik Hutan\n";
    cout << "8. Simpan Data ke File\n";
    cout << "0. Keluar\n";
    cout << "================================\n";
}

void tambahPohon(vector<Pohon> &data) {
    Pohon pohon;
    
    cout << "\n--- TAMBAH DATA POHON ---\n";
    cout << "Kode Pohon  : ";
    getline(cin, pohon.kode);
    
    // Cek apakah kode pohon sudah ada
    if(cariByKode(data, pohon.kode) != -1) {
        cout << "Error: Kode pohon sudah terdaftar!\n";
        return;
    }
    
    cout << "Nama Pohon  : ";
    getline(cin, pohon.nama);
    cout << "Famili      : ";
    getline(cin, pohon.famili);
    cout << "Lokasi      : ";
    getline(cin, pohon.lokasi);
    cout << "Tahun Tanam : ";
    cin >> pohon.tahun_tanam;
    cout << "Tinggi (m)  : ";
    cin >> pohon.tinggi;
    cout << "Diameter (cm): ";
    cin >> pohon.diameter;
    cin.ignore();
    
    // Validasi data
    if(pohon.tahun_tanam < 1000 || pohon.tahun_tanam > 2024) {
        cout << "Error: Tahun tanam harus antara 1000-2024!\n";
        return;
    }
    if(pohon.tinggi <= 0 || pohon.tinggi > 150) {
        cout << "Error: Tinggi harus antara 0.1-150 meter!\n";
        return;
    }
    if(pohon.diameter <= 0 || pohon.diameter > 1000) {
        cout << "Error: Diameter harus antara 0.1-1000 cm!\n";
        return;
    }
    
    pohon.status = true; // Default status sehat
    data.push_back(pohon);
    cout << "Data pohon berhasil ditambahkan!\n";
}

void tampilkanSemuaPohon(const vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data pohon.\n";
        return;
    }
    
    // Tampilan semua data pohon
    cout << "\n--- DATA SEMUA POHON ---\n";
    cout << "========================================================================================================\n";
    cout << left << setw(10) << "Kode" << setw(20) << "Nama Pohon" 
         << setw(15) << "Famili" << setw(15) << "Lokasi" 
         << setw(10) << "Tahun" << setw(8) << "Tinggi" 
         << setw(10) << "Diameter" << setw(10) << "Status" << endl;
    cout << "========================================================================================================\n";
    
    for(const auto &pohon : data) {
        cout << left << setw(10) << pohon.kode 
             << setw(20) << pohon.nama 
             << setw(15) << pohon.famili
             << setw(15) << pohon.lokasi
             << setw(10) << pohon.tahun_tanam
             << setw(8) << fixed << setprecision(1) << pohon.tinggi
             << setw(10) << fixed << setprecision(1) << pohon.diameter
             << setw(10) << (pohon.status ? "Sehat" : "Sakit") << endl;
    }
}

// Edit data pohon
void editPohon(vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data untuk diedit.\n";
        return;
    }
    
    string kode;
    cout << "\n--- EDIT DATA POHON ---\n";
    cout << "Masukkan Kode Pohon yang akan diedit: ";
    getline(cin, kode);
    
    // Mencari data pohon by code
    int index = cariByKode(data, kode);
    if(index == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan!\n";
        return;
    }
   
    // Menampilkan data pohon yang mau di edit
    cout << "Data ditemukan:\n";
    cout << "Kode: " << data[index].kode << ", Nama: " << data[index].nama 
         << ", Famili: " << data[index].famili << ", Lokasi: " << data[index].lokasi 
         << ", Tahun: " << data[index].tahun_tanam << ", Tinggi: " << data[index].tinggi 
         << "m, Diameter: " << data[index].diameter << "cm, Status: " << (data[index].status ? "Sehat" : "Sakit") << endl;
    
    // Edit data
    cout << "\nMasukkan data baru:\n";
    cout << "Nama Pohon  : ";
    getline(cin, data[index].nama);
    cout << "Famili      : ";
    getline(cin, data[index].famili);
    cout << "Lokasi      : ";
    getline(cin, data[index].lokasi);
    cout << "Tahun Tanam : ";
    cin >> data[index].tahun_tanam;
    cout << "Tinggi (m)  : ";
    cin >> data[index].tinggi;
    cout << "Diameter (cm): ";
    cin >> data[index].diameter;
    cin.ignore();
    
    // Validasi data
    if(data[index].tahun_tanam < 1000 || data[index].tahun_tanam > 2024) {
        cout << "Error: Tahun tanam harus antara 1000-2024! Data tidak diubah.\n";
        return;
    }
    if(data[index].tinggi <= 0 || data[index].tinggi > 150) {
        cout << "Error: Tinggi harus antara 0.1-150 meter! Data tidak diubah.\n";
        return;
    }
    if(data[index].diameter <= 0 || data[index].diameter > 1000) {
        cout << "Error: Diameter harus antara 0.1-1000 cm! Data tidak diubah.\n";
        return;
    }
    
    cout << "Data berhasil diupdate!\n";
}

// Hapus data pohon
void hapusPohon(vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data untuk dihapus.\n";
        return;
    }
    
    string kode;
    cout << "\n--- HAPUS DATA POHON ---\n";
    cout << "Masukkan Kode Pohon yang akan dihapus: ";
    getline(cin, kode);
    
    // Mencari data pohon by code
    int index = cariByKode(data, kode);
    if(index == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan!\n";
        return;
    }
    
    // Tampilkan data yang akan dihapus
    cout << "Data yang akan dihapus:\n";
    cout << "Kode: " << data[index].kode << ", Nama: " << data[index].nama 
         << ", Lokasi: " << data[index].lokasi << endl;
    
    // Konfirmasi
    char konfirmasi;
    cout << "Yakin ingin menghapus? (y/n): ";
    cin >> konfirmasi;
    cin.ignore();
    
    if(konfirmasi == 'y' || konfirmasi == 'Y') {
        data.erase(data.begin() + index);
        cout << "Data berhasil dihapus!\n";
    } else {
        cout << "Penghapusan dibatalkan.\n";
    }
}

// Tandai pohon sakit
void tandaiSakit(vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data pohon.\n";
        return;
    }
    
    string kode;
    cout << "\n--- TANDAI POHON SAKIT ---\n";
    cout << "Masukkan Kode Pohon yang sakit: ";
    getline(cin, kode);
    
    // Mencari pohon yang akan ditandai sakit
    int index = cariByKode(data, kode);
    if(index == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan!\n";
        return;
    }
    
    // Notifikasi jika pohon sudah sakit
    if(!data[index].status) {
        cout << "Pohon ini sudah ditandai sebagai sakit!\n";
        return;
    }
    
    // Tandai sebagai sakit
    data[index].status = false;
    cout << "Pohon \"" << data[index].nama << "\" berhasil ditandai sebagai sakit!\n";
}

// Tandai pohon sehat
void tandaiSehat(vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data pohon.\n";
        return;
    }
    
    string kode;
    cout << "\n--- TANDAI POHON SEHAT ---\n";
    cout << "Masukkan Kode Pohon yang sudah sehat: ";
    getline(cin, kode);
    
    // Mencari pohon yang akan ditandai sehat
    int index = cariByKode(data, kode);
    if(index == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan!\n";
        return;
    }
    
    // Notifikasi jika pohon sudah sehat
    if(data[index].status) {
        cout << "Pohon ini sudah dalam kondisi sehat!\n";
        return;
    }
    
    // Tandai sebagai sehat
    data[index].status = true;
    cout << "Pohon \"" << data[index].nama << "\" berhasil ditandai sebagai sehat!\n";
}

// Hitung statistik
void hitungStatistik(const vector<Pohon> &data) {
    if(data.empty()) {
        cout << "\nTidak ada data untuk dihitung.\n";
        return;
    }
    
    int totalPohon = data.size();
    int sehat = 0;
    int sakit = 0;
    int tahunTerlama = data[0].tahun_tanam;
    int tahunTerbaru = data[0].tahun_tanam;
    double totalTinggi = 0;
    double totalDiameter = 0;
    double tinggiTertinggi = data[0].tinggi;
    double diameterTerbesar = data[0].diameter;
    
    for(const auto &pohon : data) {
        if(pohon.status) sehat++;
        else sakit++;
        
        if(pohon.tahun_tanam < tahunTerlama) tahunTerlama = pohon.tahun_tanam;
        if(pohon.tahun_tanam > tahunTerbaru) tahunTerbaru = pohon.tahun_tanam;
        
        totalTinggi += pohon.tinggi;
        totalDiameter += pohon.diameter;
        
        if(pohon.tinggi > tinggiTertinggi) tinggiTertinggi = pohon.tinggi;
        if(pohon.diameter > diameterTerbesar) diameterTerbesar = pohon.diameter;
    }
    
    double rataTinggi = totalTinggi / totalPohon;
    double rataDiameter = totalDiameter / totalPohon;
    
    // Menu statistik hutan
    cout << "\n--- STATISTIK HUTAN ---\n";
    cout << "Total Pohon        : " << totalPohon << endl;
    cout << "Pohon Sehat        : " << sehat << endl;
    cout << "Pohon Sakit        : " << sakit << endl;
    cout << "Tahun Tanam Tertua : " << tahunTerlama << endl;
    cout << "Tahun Tanam Terbaru: " << tahunTerbaru << endl;
    cout << fixed << setprecision(2);
    cout << "Rata-rata Tinggi   : " << rataTinggi << " m" << endl;
    cout << "Rata-rata Diameter : " << rataDiameter << " cm" << endl;
    cout << "Tinggi Tertinggi   : " << tinggiTertinggi << " m" << endl;
    cout << "Diameter Terbesar  : " << diameterTerbesar << " cm" << endl;
    cout << "Persentase Sehat   : " << (static_cast<double>(sehat) / totalPohon * 100) << "%" << endl;
}

// Simpan data kehutanan kedalam file data_kehutanan.txt
void simpanKeFile(const vector<Pohon> &data) {
    ofstream file("data_kehutanan.txt");
    
    if(!file.is_open()) {
        cout << "Error: Gagal membuka file untuk penyimpanan!\n";
        return;
    }
    
    for(const auto &pohon : data) {
        file << pohon.kode << "," << pohon.nama << "," 
             << pohon.famili << "," << pohon.lokasi << "," 
             << pohon.tahun_tanam << "," << pohon.tinggi << ","
             << pohon.diameter << "," << (pohon.status ? "1" : "0") << endl;
    }
    
    // Notifikasi data berhasil disimpan
    file.close();
    cout << "Data berhasil disimpan ke file! (" << data.size() << " records)\n";
}

// Membaca data dari file data_kehutanan.txt
void bacaDataDariFile(vector<Pohon> &data) {
    ifstream file("data_kehutanan.txt");
    
    // Notifikasi data tidak ditemukan, dan akan dibuat file baru
    if(!file.is_open()) {
        cout << "File data tidak ditemukan. Akan dibuat file baru.\n";
        return;
    }
    
    string line;
    data.clear(); // Clear data sebelum membaca dari file
    
    while(getline(file, line)) {
        if(line.empty()) continue;
        
        stringstream ss(line);
        string item;
        Pohon pohon;
        
        // Format data file: kode,nama,famili,lokasi,tahun_tanam,tinggi,diameter,status
        getline(ss, pohon.kode, ',');
        getline(ss, pohon.nama, ',');
        getline(ss, pohon.famili, ',');
        getline(ss, pohon.lokasi, ',');
        
        getline(ss, item, ',');
        try {
            pohon.tahun_tanam = stoi(item);
        } catch (const exception& e) {
            cout << "Error membaca tahun tanam untuk pohon: " << pohon.nama << endl;
            continue;
        }
        
        getline(ss, item, ',');
        try {
            pohon.tinggi = stod(item);
        } catch (const exception& e) {
            cout << "Error membaca tinggi untuk pohon: " << pohon.nama << endl;
            continue;
        }
        
        getline(ss, item, ',');
        try {
            pohon.diameter = stod(item);
        } catch (const exception& e) {
            cout << "Error membaca diameter untuk pohon: " << pohon.nama << endl;
            continue;
        }
        
        getline(ss, item, ',');
        pohon.status = (item == "1");
        
        data.push_back(pohon);
    }
    
    file.close();
}

int cariByKode(const vector<Pohon> &data, const string &kode) {
    for(size_t i = 0; i < data.size(); i++) {
        if(data[i].kode == kode) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
