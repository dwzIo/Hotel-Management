#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// =========================================================
// STRUCT DEFINITION
// =========================================================
struct Tamu {
    string namaUtama;
    string noHP;
    int totalOrang;
    string namaAnggota[4];
};

struct Kamar {
    int noKamar;
    int lantai;
    string tipe;
    long hargaPerHari;
    bool isTerisi;
    string tglCheckIn;
    string tglCheckOut;
    int durasi;
    long totalBayar;
    Tamu dataTamu;
};

Kamar hotel[30];
int totalKamar = 30;

// =========================================================
// MATERI POINTER: FUNGSI PENCARIAN DENGAN RETURN POINTER
// =========================================================
// Fungsi ini mengembalikan alamat memori (pointer) dari objek Kamar
Kamar* cariKamarDenganPointer(int no) {
    for (int i = 0; i < totalKamar; i++) {
        if (hotel[i].noKamar == no) {
            return &hotel[i]; // Mengembalikan alamat index ke-i
        }
    }
    return nullptr; // Jika tidak ditemukan
}

// =========================================================
// UTILITY & REKURSIF
// =========================================================
string hitungCheckout(string tglIn, int durasi) {
    int d = stoi(tglIn.substr(0, 2));
    int m = stoi(tglIn.substr(3, 2));
    int y = stoi(tglIn.substr(6, 4));
    d += durasi;
    while (d > 30) { d -= 30; m++; if (m > 12) { m = 1; y++; } }
    return (d < 10 ? "0" : "") + to_string(d) + "-" + (m < 10 ? "0" : "") + to_string(m) + "-" + to_string(y);
}

long hitungPendapatanRekursif(int n) {
    if (n < 0) return 0;
    long bayar = (hotel[n].isTerisi) ? hotel[n].totalBayar : 0;
    return bayar + hitungPendapatanRekursif(n - 1);
}

// =========================================================
// SORTING NAMA
// =========================================================
void sortNama(bool asc) {
    for (int i = 0; i < totalKamar - 1; i++) {
        for (int j = 0; j < totalKamar - i - 1; j++) {
            if (hotel[j].isTerisi && hotel[j+1].isTerisi) {
                if (asc ? (hotel[j].dataTamu.namaUtama > hotel[j+1].dataTamu.namaUtama) : (hotel[j].dataTamu.namaUtama < hotel[j+1].dataTamu.namaUtama)) {
                    swap(hotel[j], hotel[j+1]);
                }
            }
        }
    }
}

// =========================================================
// MENU FUNCTIONS
// =========================================================
void menuPemesanan() {
    string tgl; int dur;
    cout << "\n--- PEMESANAN ---\nTanggal Check-in (DD-MM-YYYY): "; cin >> tgl;
    cout << "Durasi menginap (hari): "; cin >> dur;

    cout << "\n[ STANDAR - Rp1jt/hr ]: ";
    for(int i=0; i<totalKamar; i++) if(!hotel[i].isTerisi && hotel[i].tipe == "Standar") cout << hotel[i].noKamar << " ";
    cout << "\n[ PREMIUM - Rp3jt/hr ]: ";
    for(int i=0; i<totalKamar; i++) if(!hotel[i].isTerisi && hotel[i].tipe == "Premium") cout << hotel[i].noKamar << " ";

    int pilih; cout << "\n\nPilih No Kamar: "; cin >> pilih;
    
    // PENERAPAN POINTER
    Kamar* ptrKamar = cariKamarDenganPointer(pilih);

    if (ptrKamar != nullptr && !ptrKamar->isTerisi) {
        cout << "Nama Utama: "; cin.ignore(); getline(cin, ptrKamar->dataTamu.namaUtama);
        cout << "No HP: "; cin >> ptrKamar->dataTamu.noHP;
        cout << "Total Orang: "; cin >> ptrKamar->dataTamu.totalOrang;
        
        for(int i=0; i < ptrKamar->dataTamu.totalOrang; i++) {
            cout << "Nama Tamu " << i+1 << ": "; cin.ignore(); getline(cin, ptrKamar->dataTamu.namaAnggota[i]);
        }

        long total = ptrKamar->hargaPerHari * dur;
        cout << "\n--- KONFIRMASI ---\nKamar: " << ptrKamar->noKamar << "\nTotal: Rp" << total << "\nBayar? (y/n): ";
        char y; cin >> y;

        if (y == 'y' || y == 'Y') {
            ptrKamar->isTerisi = true;
            ptrKamar->tglCheckIn = tgl;
            ptrKamar->durasi = dur;
            ptrKamar->tglCheckOut = hitungCheckout(tgl, dur);
            ptrKamar->totalBayar = total;
            cout << "TRANSAKSI BERHASIL! Check-out: " << ptrKamar->tglCheckOut << endl;
        }
    } else cout << "Kamar tidak tersedia!\n";
}

void menuCheckout() {
    int no; cout << "\nMasukkan No Kamar: "; cin >> no;
    Kamar* ptr = cariKamarDenganPointer(no);

    if (ptr != nullptr && ptr->isTerisi) {
        cout << "Nama: " << ptr->dataTamu.namaUtama << " | In: " << ptr->tglCheckIn << endl;
        cout << "Konfirmasi Checkout? (y/n): "; char y; cin >> y;
        if(y == 'y') {
            ptr->isTerisi = false;
            ptr->tglCheckIn = ""; // Reset tanggal
            cout << "Checkout Berhasil!\n";
        }
    } else cout << "Data tidak ditemukan.\n";
}

void menuDataRiwayat() {
    cout << "Urutkan Nama (1.A-Z / 2.Z-A / 3.Tidak): "; int s; cin >> s;
    if(s==1) sortNama(true); else if(s==2) sortNama(false);

    cout << "\n" << left << setw(8) << "Kamar" << setw(10) << "Lantai" << setw(15) << "Tamu" << setw(15) << "Check-In" << setw(15) << "Check-Out" << "Status" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < totalKamar; i++) {
        cout << left << setw(8) << hotel[i].noKamar << setw(10) << hotel[i].lantai 
             << setw(15) << (hotel[i].isTerisi ? hotel[i].dataTamu.namaUtama : "-")
             << setw(15) << (hotel[i].isTerisi ? hotel[i].tglCheckIn : "-")
             << setw(15) << (hotel[i].isTerisi ? hotel[i].tglCheckOut : "-")
             << (hotel[i].isTerisi ? "TERISI" : "KOSONG") << endl;
    }
    cout << "\nTotal Pendapatan (Rekursif): Rp" << hitungPendapatanRekursif(totalKamar-1) << endl;
}

void inisialisasi() {
    for (int i = 0; i < totalKamar; i++) {
        hotel[i].noKamar = (i < 10 ? 101+i : (i < 20 ? 201+(i-10) : 301+(i-20)));
        hotel[i].lantai = (i < 10 ? 1 : (i < 20 ? 2 : 3));
        hotel[i].tipe = (i % 2 == 0 ? "Standar" : "Premium");
        hotel[i].hargaPerHari = (hotel[i].tipe == "Standar" ? 1000000 : 3000000);
        hotel[i].isTerisi = false;
    }
}

int main() {
    inisialisasi();
    int p;
    do {
        cout << "\n[ HOTEL VETERAN YOGYAKARTA ]\n1. Pemesanan\n2. Checkout\n3. Data & Riwayat\n4. Exit\nPilih: "; cin >> p;
        if(p==1) menuPemesanan(); else if(p==2) menuCheckout(); else if(p==3) menuDataRiwayat();
    } while(p!=4);
    return 0;
}
