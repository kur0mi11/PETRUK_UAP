#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <stack>
using namespace std;

struct Perangkat {
    string nama;
    int watt;
    int manfaat;
    double jam_pakai; 
};

struct HasilKnapsack {
    int totalManfaat;
    vector<Perangkat> perangkatTerpilih;
};

void judul() {
cout << endl << endl;
cout << "        $$$$$$\\ $$\\      $$\\ $$$$$$\\ $$$$$$$\\$$$$$$$$\\       $$\\   $$\\ $$$$$$\\ $$\\      $$\\$$$$$$$$\\       $$$$$$$$\\$$\\   $$\\$$$$$$$$\\$$$$$$$\\  $$$$$$\\$$\\     $$\\ " << endl;
cout << "       $$  __$$\\$$$\\    $$$ $$  __$$\\$$  __$$\\__$$  __|      $$ |  $$ $$  __$$\\$$$\\    $$$ $$  _____|      $$  _____$$$\\  $$ $$  _____$$  __$$\\$$  __$$\\$$\\   $$  |" << endl;
cout << "       $$ /  \\__$$$$\\  $$$$ $$ /  $$ $$ |  $$ | $$ |         $$ |  $$ $$ /  $$ $$$$\\  $$$$ $$ |            $$ |     $$$$\\ $$ $$ |     $$ |  $$ $$ /  \\__\\$$\\ $$  / " << endl;
cout << "       \\$$$$$$\\ $$\\$$\\$$ $$ $$$$$$$$ $$$$$$$  | $$ |         $$$$$$$$ $$ |  $$ $$\\$$\\$$ $$ $$$$$\\          $$$$$\\   $$ $$\\$$ $$$$$\\   $$$$$$$  $$ |$$$$\\ \\$$$$  /  " << endl;
cout << "        \\____$$\\$$ \\$$$  $$ $$  __$$ $$  __$$<  $$ |         $$  __$$ $$ |  $$ $$ \\$$$  $$ $$  __|         $$  __|  $$ \\$$$$ $$  __|  $$  __$$<$$ |\\_$$ | \\$$  /   " << endl;
cout << "       $$\\   $$ $$ |\\$  /$$ $$ |  $$ $$ |  $$ | $$ |         $$ |  $$ $$ |  $$ $$ |\\$  /$$ $$ |            $$ |     $$ |\\$$$ $$ |     $$ |  $$ $$ |  $$ |  $$ |    " << endl;
cout << "       \\$$$$$$  $$ | \\_/ $$ $$ |  $$ $$ |  $$ | $$ |         $$ |  $$ |$$$$$$  $$ | \\_/ $$ $$$$$$$$\\       $$$$$$$$\\$$ | \\$$ $$$$$$$$\\$$ |  $$ \\$$$$$$  |  $$ |    " << endl;
cout << "        \\______/\\__|     \\__\\__|  \\__\\__|  \\__| \\__|         \\__|  \\__|\\______/\\__|     \\__\\________|      \\________\\__|  \\__\\________\\__|  \\__|\\______/   \\__|    " << endl;
cout << endl<< endl;
}

const int JUMLAH_PERANGKAT = 12;
Perangkat perangkatArray[JUMLAH_PERANGKAT] = {
    {"AC", 1000, 8},
    {"Blender", 200, 5},
    {"Dispenser", 400, 6},
    {"Kipas Angin", 80, 4},
    {"Kompor Listrik", 900, 7},
    {"Kulkas", 150, 9},
    {"Lampu", 15, 3},
    {"Mesin Cuci", 500, 6},
    {"Microwave", 1200, 6},
    {"Rice Cooker", 300, 7},
    {"Setrika", 400, 4},
    {"Televisi", 250, 7}
};

void tampilkanPerangkatPointer(const Perangkat* p) {
    if (p != nullptr) {
        cout << "- " << p->nama << " (" << p->watt << "W, manfaat: " << p->manfaat << ")\n";
    }
}

void tampilkanPerangkat() {
    cout << "\n============================================================\n";
    cout << " DAFTAR PERANGKAT ELEKTRONIK\n";
    cout << "============================================================\n";
    for (int i = 0; i < JUMLAH_PERANGKAT; i++) {
        tampilkanPerangkatPointer(&perangkatArray[i]);
    }
}

void tampilkanJamMenit(double jam) {
    int jam_utuh = (int)jam;
    int menit = (int)round((jam - jam_utuh) * 60);
    cout << jam_utuh << " jam " << menit << " menit";
}

HasilKnapsack knapsack(vector<Perangkat>& perangkat, int batasDaya) {
    int n = perangkat.size();
    vector<vector<int>> dp(n + 1, vector<int>(batasDaya + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= batasDaya; w++) {
            if (perangkat[i - 1].watt <= w) {
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - perangkat[i - 1].watt] + perangkat[i - 1].manfaat);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    stack<Perangkat> stackPerangkat;
    int w = batasDaya;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            stackPerangkat.push(perangkat[i - 1]);
            w -= perangkat[i - 1].watt;
        }
    }

    vector<Perangkat> terpilih;
    while (!stackPerangkat.empty()) {
        terpilih.push_back(stackPerangkat.top());
        stackPerangkat.pop();
    }

    return HasilKnapsack{dp[n][batasDaya], terpilih};
}

int main() {
    judul();
    char namaInput[100];
    char konfirmasi;
    vector<Perangkat> perangkatTerpilih;

    while (true) {
        perangkatTerpilih.clear();
        tampilkanPerangkat();

        cout << "\nMasukkan nama perangkat yang ingin digunakan satu per satu (ketik 'selesai' untuk berhenti):\n";
        while (true) {
            cout << "> ";
            cin.getline(namaInput, 100);

            if (strcasecmp(namaInput, "selesai") == 0) break;

            bool ditemukan = false;
            for (int i = 0; i < JUMLAH_PERANGKAT; i++) {
                if (strcasecmp(perangkatArray[i].nama.c_str(), namaInput) == 0) {
                    perangkatTerpilih.push_back(perangkatArray[i]);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Nama perangkat tidak ditemukan. Silakan masukkan lagi.\n";
            }
        }

        cout << "\nPerangkat yang Anda pilih:\n";
        for (size_t i = 0; i < perangkatTerpilih.size(); i++) {
            cout << "- " << perangkatTerpilih[i].nama << " (" << perangkatTerpilih[i].watt << "W, manfaat: " << perangkatTerpilih[i].manfaat << ")\n";
        }

        cout << "\nApakah data sudah benar? (y/n): ";
        cin >> konfirmasi;
        cin.ignore();

        if (konfirmasi == 'y' || konfirmasi == 'Y') break;

        cout << "\nSilakan ulangi input.\n";
    }

    int batasDaya;
    cout << "\nMasukkan batas konsumsi daya harian (Watt): ";
    cin >> batasDaya;
    cin.ignore();

    HasilKnapsack hasilKnapsack = knapsack(perangkatTerpilih, batasDaya);
	vector<Perangkat> solusi = hasilKnapsack.perangkatTerpilih;
	int manfaatTotal = hasilKnapsack.totalManfaat;

    for (size_t i = 0; i < solusi.size(); i++) {
        if (solusi[i].nama == "Kulkas") {
            solusi[i].jam_pakai = 24;
        } else if (solusi[i].nama == "AC") {
            solusi[i].jam_pakai = 8;
        } else if (solusi[i].nama == "Lampu") {
            solusi[i].jam_pakai = 12;
        } else {
            solusi[i].jam_pakai = min(6.0, 24.0 * (solusi[i].manfaat / (double)manfaatTotal));
        }
    }

    double totalKonsumsi = 0;
    for (size_t i = 0; i < solusi.size(); i++) {
        totalKonsumsi += solusi[i].watt * solusi[i].jam_pakai;
    }

    cout << "\n============================================================\n";
    cout << " REKOMENDASI PENGGUNAAN PERANGKAT ELEKTRONIK\n";
    cout << "============================================================\n";
    for (size_t i = 0; i < solusi.size(); i++) {
        const Perangkat* p = &solusi[i];
        cout << "- " << p->nama << ": ";
        tampilkanJamMenit(p->jam_pakai);
        cout << " (Konsumsi: " << (int)(p->watt * p->jam_pakai) << " Wh)\n";
    }

    cout << "\nTotal Manfaat: " << manfaatTotal << "\n";
    cout << "Total Konsumsi Energi: " << (int)totalKonsumsi << " Wh (Batas: " << batasDaya << " Wh)\n";
    cout << "Persentase Penggunaan: " << (int)((totalKonsumsi / batasDaya) * 100) << "%\n";

    return 0;
}
