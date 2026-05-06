#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// Struct untuk status fisik kamar
struct Kamar {
    int lantai;
    int nomor;
    char tipe[15];
    double harga;
    int tersedia; // 1=Kosong, 0=Terisi
};

// Struct untuk data tamu
struct Transaksi {
    char tanggal[15];
    int lantai;
    int noKamar;
    char nama[50];
    char noHp[15];
    int statusCheckIn; // 1=checkin, 0=checkout
};

// awal 3 lantai, masing-masing 10 kamar
Kamar hotel[3][10];

// looping kamar dari lantai 1 sampai 3
void inisialisasiHotel() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            hotel[i][j].lantai = i + 1;
            hotel[i][j].nomor = (i + 1) * 100 + (j + 1); // kamar 101-110, 201-210, dst
            hotel[i][j].tersedia = 1; // 1=artinya tersedia
            strcpy(hotel[i][j].tipe, "-");
            hotel[i][j].harga = 0;
        }
    }
}

int main() {

}