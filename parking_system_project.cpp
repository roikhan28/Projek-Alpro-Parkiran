#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Vehicle {
    string nomorPlat;
    string jenisKendaraan;
    string tanggalMasuk;
    string waktuMasuk;
};

const string namaFile = "parking_datav2.txt";
int kapasitasMaksimal = 100;
Vehicle* kendaraanParkir = nullptr; 
int jumlahKendaraan = 0;

bool alokasiMemori(int kapasitasBaru) {
    Vehicle* temp = new Vehicle[kapasitasBaru];
    if (temp == nullptr) {
        cout << "\nGagal mengalokasikan memori!\n";
        return false;
    }
    if (kendaraanParkir != nullptr) {
        for (int i = 0; i < jumlahKendaraan; ++i) {
            temp[i] = kendaraanParkir[i];
        }
        delete[] kendaraanParkir;
    }
    kendaraanParkir = temp;
    kapasitasMaksimal = kapasitasBaru;
    return true;
}

bool cariKendaraan(const string& nomorPlat) {
    for (int i = 0; i < jumlahKendaraan; ++i) {
        if (kendaraanParkir[i].nomorPlat == nomorPlat) {
            return true;
        }
    }
    return false;
}

int hitungJumlahKendaraanRekursif(int index) {
    if (index < 0) {
        return 0;
    }
    return 1 + hitungJumlahKendaraanRekursif(index - 1);
}

void simpanKeFile() {
    ofstream file(namaFile);
    if (!file.is_open()) {
        cout << "\nError saat menyimpan data ke file!\n";
        return;
    }

    file << jumlahKendaraan << "\n";
    file << kapasitasMaksimal << "\n";
    for (int i = 0; i < jumlahKendaraan; ++i) {
        file << kendaraanParkir[i].nomorPlat << "\n";
        file << kendaraanParkir[i].jenisKendaraan << "\n";
        file << kendaraanParkir[i].tanggalMasuk << "\n";
        file << kendaraanParkir[i].waktuMasuk << "\n";
    }
}

void loadFile() {
    ifstream file(namaFile);
    if (file.is_open()) {
        file >> jumlahKendaraan;
        file >> kapasitasMaksimal;
        file.ignore();

        if (jumlahKendaraan > kapasitasMaksimal) {
            kapasitasMaksimal = jumlahKendaraan;
        }

        if (jumlahKendaraan > 0) {
            if (alokasiMemori(kapasitasMaksimal)) {
                for (int i = 0; i < jumlahKendaraan; ++i) {
                    getline(file, kendaraanParkir[i].nomorPlat);
                    getline(file, kendaraanParkir[i].jenisKendaraan);
                    getline(file, kendaraanParkir[i].tanggalMasuk);
                    getline(file, kendaraanParkir[i].waktuMasuk);
                }
            }
        }
    } else {
        alokasiMemori(kapasitasMaksimal);
        if (!alokasiMemori(kapasitasMaksimal)) {
            cout << "Gagal alokasi memori saat membuka file.\n";
            jumlahKendaraan = 0;
            return;
        }
    }
}

void cooldown() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanMenu() {
    system("cls");
    cout << "\n=== Sistem Manajemen Parkir ===\n";
    cout << "1. Kendaraan Masuk\n";
    cout << "2. Kendaraan Keluar\n";
    cout << "3. Tampilkan Kendaraan yang Parkir\n";
    cout << "4. Urutkan Kendaraan berdasarkan Nomor Plat\n";
    cout << "5. Cari Kendaraan\n";
    cout << "6. Bersihkan Data Parkir\n";
    cout << "7. Hitung Jumlah Kendaraan\n";
    cout << "8. Keluar Program\n";
    cout << "Pilihan Anda: ";
}

void kendaraanMasuk() {
    if (jumlahKendaraan >= kapasitasMaksimal) {
        int kapasitasBaru = kapasitasMaksimal * 2;
        if (!alokasiMemori(kapasitasBaru)) {
            return;
        }
        cout << "\nKapasitas parkir diperbesar menjadi " << kapasitasMaksimal << ".\n";
    }

    Vehicle kendaraanBaru;
    cout << "\nMasukkan Nomor Plat: ";
    getline(cin, kendaraanBaru.nomorPlat);

    if (cariKendaraan(kendaraanBaru.nomorPlat)) {
        cout << "\nKendaraan dengan nomor plat ini sudah terparkir!\n";
        cooldown();
        return;
    }

    cout << "Masukkan Jenis Kendaraan (mobil/motor/truk): ";
    getline(cin, kendaraanBaru.jenisKendaraan);

    cout << "Masukkan Tanggal Masuk (DD-MM-YYYY): ";
    getline(cin, kendaraanBaru.tanggalMasuk);

    cout << "Masukkan Waktu Masuk (HH:MM): ";
    getline(cin, kendaraanBaru.waktuMasuk);

    kendaraanParkir[jumlahKendaraan++] = kendaraanBaru;
    simpanKeFile();

    cout << "\nKendaraan berhasil diparkir.\n";
    cooldown();
}

void kendaraanKeluar() {
    if (jumlahKendaraan == 0) {
        cout << "\nParkir kosong!\n";
        cooldown();
        return;
    }

    string nomorPlat;
    cout << "\nMasukkan Nomor Plat kendaraan yang keluar: ";
    getline(cin >> ws, nomorPlat);

    int indexDitemukan = -1;
    for (int i = 0; i < jumlahKendaraan; ++i) {
        if (kendaraanParkir[i].nomorPlat == nomorPlat) {
            indexDitemukan = i;
            break;
        }
    }

    if (indexDitemukan != -1) {
        cout << "\nDetail Kendaraan:\n";
        cout << "----------------------------\n";
        cout << "Nomor Plat:    " << kendaraanParkir[indexDitemukan].nomorPlat << "\n";
        cout << "Jenis:         " << kendaraanParkir[indexDitemukan].jenisKendaraan << "\n";
        cout << "Tanggal Masuk: " << kendaraanParkir[indexDitemukan].tanggalMasuk << "\n";
        cout << "Waktu Masuk:   " << kendaraanParkir[indexDitemukan].waktuMasuk << "\n";
        cout << "----------------------------\n";

        for (int i = indexDitemukan; i < jumlahKendaraan - 1; ++i) {
            kendaraanParkir[i] = kendaraanParkir[i + 1];
        }
        jumlahKendaraan--;
        simpanKeFile();

        cout << "Kendaraan berhasil keluar.\n";
    } else {
        cout << "\nKendaraan tidak ditemukan!\n";
    }
    cooldown();
}

void outputKendaraan() {
    if (kendaraanParkir == nullptr) {
        cout << "\nError: Memori belum dialokasikan untuk daftar kendaraan!\n";
        cooldown();
        return;
    }
    if (jumlahKendaraan == 0) {
        cout << "\nTidak ada kendaraan yang sedang parkir.\n";
    } else {
        cout << "\nKendaraan yang Parkir (" << jumlahKendaraan << "):\n";
        cout << "+-----------------+---------------+-------------+----------+\n";
        cout << "| Nomor Plat      | Jenis         | Tanggal     | Waktu    |\n";
        cout << "+-----------------+---------------+-------------+----------+\n";

        for (int i = 0; i < jumlahKendaraan; ++i) {
            cout << "| " << setw(15) << left << kendaraanParkir[i].nomorPlat << " | "
                 << setw(13) << left << kendaraanParkir[i].jenisKendaraan << " | "
                 << setw(11) << left << kendaraanParkir[i].tanggalMasuk << " | "
                 << setw(8) << left << kendaraanParkir[i].waktuMasuk << " |\n";
        }
        cout << "+-----------------+---------------+-------------+----------+\n";
    }
    cooldown();
}

void urutkanBerdasarkanNomorPlat() {
    if (jumlahKendaraan == 0) {
        cout << "\nTidak ada kendaraan untuk diurutkan.\n";
        cooldown();
        return;
    }

    for (int i = 0; i < jumlahKendaraan - 1; ++i) {
        for (int j = 0; j < jumlahKendaraan - i - 1; ++j) {
            if (kendaraanParkir[j].nomorPlat > kendaraanParkir[j + 1].nomorPlat) {
                swap(kendaraanParkir[j], kendaraanParkir[j + 1]);
            }
        }
    }

    cout << "\nKendaraan berhasil diurutkan berdasarkan nomor plat.\n";
    cooldown();
}

void cariKendaraan() {
    string nomorPlat;
    cout << "\nMasukkan Nomor Plat yang ingin dicari: ";
    getline(cin, nomorPlat);

    for (int i = 0; i < jumlahKendaraan; ++i) {
        if (kendaraanParkir[i].nomorPlat == nomorPlat) {
            cout << "\nKendaraan Ditemukan:\n";
            cout << "----------------------------\n";
            cout << "Nomor Plat:    " << kendaraanParkir[i].nomorPlat << "\n";
            cout << "Jenis:         " << kendaraanParkir[i].jenisKendaraan << "\n";
            cout << "Tanggal Masuk: " << kendaraanParkir[i].tanggalMasuk << "\n";
            cout << "Waktu Masuk:   " << kendaraanParkir[i].waktuMasuk << "\n";
            cout << "----------------------------\n";
            cooldown();
            return;
        }
    }

    cout << "\nKendaraan tidak ditemukan!\n";
    cooldown();
}

void bersihkanData() {
    jumlahKendaraan = 0;
    simpanKeFile();
    cout << "\nSemua data parkir telah dibersihkan.\n";
    cooldown();
}

int main() {
    loadFile();

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: kendaraanMasuk(); break;
            case 2: kendaraanKeluar(); break;
            case 3: outputKendaraan(); break;
            case 4: urutkanBerdasarkanNomorPlat(); break;
            case 5: cariKendaraan(); break;
            case 6: bersihkanData(); break;
            case 7: 
                cout << "\nJumlah kendaraan parkir: " 
                     << hitungJumlahKendaraanRekursif(jumlahKendaraan - 1) << "\n"; 
                cooldown(); 
                break;
            case 8:
                simpanKeFile();
                cout << "\nKeluar dari program...\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                cooldown();
        }
    } while (pilihan != 8);

    delete[] kendaraanParkir;
    kendaraanParkir = nullptr;

    return 0;
}
