#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct nilai {
    float Mtk, BIn, Big, IPA;
};

struct siswa {
    string nama, NISN, jurusan;
    nilai Nilai;
    float nilaiAkhir;
};


float hitungNilaiAkhir(nilai n) {
    return 0.35 * n.Mtk + 0.25 * n.IPA + 0.2 * n.BIn + 0.2 * n.Big;
}


void simpanDataKeFile(siswa data[], int jumlah) {
    ofstream file("Raport.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        file << "Nama: " << data[i].nama << '\n';
        file << "NISN: " << data[i].NISN << '\n';
        file << "Jurusan: " << data[i].jurusan << '\n';
        file << "Nilai MTK: " << data[i].Nilai.Mtk << '\n';
        file << "Nilai B. Indo: " << data[i].Nilai.BIn << '\n';
        file << "Nilai B. Inggris: " << data[i].Nilai.Big << '\n';
        file << "Nilai IPA: " << data[i].Nilai.IPA << '\n';
        file << "--------------------\n";
    }

    file.close();
}


void bacaDataDariFile(siswa data[], int &jumlah) {
    ifstream file("Raport.txt");
    if (!file) {
        jumlah = 0;
        return;
    }

    jumlah = 0;
    while (jumlah < 100) {
        siswa s;
        string label;

        if (!(file >> label) || label != "Nama:") break;
        file >> ws; getline(file, s.nama);

        if (!(file >> label) || label != "NISN:") break;
        file >> ws; getline(file, s.NISN);

        if (!(file >> label) || label != "Jurusan:") break;
        file >> ws; getline(file, s.jurusan);

        if (!(file >> label) || label != "Nilai") break;
        file >> label; // "MTK:"
        file >> s.Nilai.Mtk;

        file >> label; // "Nilai"
        file >> label; // "B."
        file >> label; // "Indo:"
        file >> s.Nilai.BIn;

        file >> label; // "Nilai"
        file >> label; // "B."
        file >> label; // "Inggris:"
        file >> s.Nilai.Big;

        file >> label; // "Nilai"
        file >> label; // "IPA:"
        file >> s.Nilai.IPA;

        s.nilaiAkhir = hitungNilaiAkhir(s.Nilai);
        data[jumlah] = s;
        jumlah++;

        string garis;
        getline(file, garis);
        getline(file, garis);
    }
    file.close();
}


void tambahData(siswa data[], int &jumlah) {
    if (jumlah >= 100) {
        cout << "Data siswa penuh\n";
        return;
    }

    siswa s;
    cout << "Masukkan Nama: ";
    getline(cin >> ws, s.nama);
    cout << "Masukkan NISN: ";
    cin >> s.NISN;
    cout << "Masukkan Jurusan: ";
    getline(cin >> ws, s.jurusan);

    cout << "Nilai MTK: "; cin >> s.Nilai.Mtk;
    cout << "Nilai B. Indo: "; cin >> s.Nilai.BIn;
    cout << "Nilai B. Inggris: "; cin >> s.Nilai.Big;
    cout << "Nilai IPA: "; cin >> s.Nilai.IPA;

    s.nilaiAkhir = hitungNilaiAkhir(s.Nilai);
    data[jumlah] = s;
    jumlah++;

    simpanDataKeFile(data, jumlah);
    cout << "\nData siswa berhasil ditambahkan dan disimpan ke Raport.txt\n";
}


void tampilData(siswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data siswa\n";
        return;
    }

    cout << "\n=== DATA SISWA ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "Nama: " << data[i].nama << endl;
        cout << "NISN: " << data[i].NISN << endl;
        cout << "Jurusan: " << data[i].jurusan << endl;
        cout << "Nilai MTK: " << data[i].Nilai.Mtk << endl;
        cout << "Nilai B. Indo: " << data[i].Nilai.BIn << endl;
        cout << "Nilai B. Inggris: " << data[i].Nilai.Big << endl;
        cout << "Nilai IPA: " << data[i].Nilai.IPA << endl;
        cout << "Nilai Akhir: " << data[i].nilaiAkhir << endl;
        cout << "--------------------\n";
    }
}


void cariSiswa(siswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data siswa\n";
        return;
    }

    string cari;
    cout << "Masukkan NISN yang dicari: ";
    cin >> cari;

    bool ketemu = false;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].NISN == cari) {
            cout << "\nData ditemukan:\n";
            cout << "Nama: " << data[i].nama << endl;
            cout << "Jurusan: " << data[i].jurusan << endl;
            cout << "Nilai Akhir: " << data[i].nilaiAkhir << endl;
            ketemu = true;
            break;
        }
    }

    if (!ketemu) cout << "Data dengan NISN " << cari << " tidak ditemukan\n";
}


void ranking(siswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data siswa\n";
        return;
    }

    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].nilaiAkhir < data[j + 1].nilaiAkhir) {
                siswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    cout << "\n=== RANKING SISWA ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << data[i].nama
             << " - Nilai Akhir: " << data[i].nilaiAkhir << endl;
    }
}


int main() {
    siswa data[100];
    int jumlah = 0;
    int pilihan;

    bacaDataDariFile(data, jumlah);

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampil Data\n";
        cout << "3. Cari Siswa\n";
        cout << "4. Ranking\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahData(data, jumlah); break;
            case 2: tampilData(data, jumlah); break;
            case 3: cariSiswa(data, jumlah); break;
            case 4: ranking(data, jumlah); break;
            case 0: cout << "Keluar dari program\n"; break;
            default: cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 0);

    return 0;
}
