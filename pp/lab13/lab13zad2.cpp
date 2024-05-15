#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct SKonto {
    string nr_konta, imie, nazwisko, data;
    int id_transakcji;
    double kwota;
};

bool wczytaj(const char* plik_wyj, SKonto*& konta, int& n) {
    if (n < 1) {
        cerr << "Nie udalo sie utworzyc tablice o rozmiarze: " << n << endl;
        return 0;
    }

    konta = new SKonto[n];
    ifstream fin(plik_wyj);
    if (!fin.good()) {
        cerr << "Blad otwarcia pliku wejsciowego\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }

    for (int i = 0; i<n; i++) {
        if (!(fin >> konta[i].nr_konta)) {
            cerr << "Blad wczytywania numeru konta!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
        if (!(fin >> konta[i].imie)) {
            cerr << "Blad wczytywania imienia!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
        if (!(fin >> konta[i].nazwisko)) {
            cerr << "Blad wczytywania nazwiska!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
        if (!(fin >> konta[i].id_transakcji)) {
            cerr << "Blad wczytywania id transakcji!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
        if (!(fin >> konta[i].data)) {
            cerr << "Blad wczytywania daty!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
        if (!(fin >> konta[i].kwota)) {
            cerr << "Blad wczytywania kwoty!\n";
            fin.ignore();
            fin.clear();
            fin.close();
            if (konta != nullptr) {
                delete[] konta;
                konta = nullptr;
            }
            return 0;
        }
    }

    return 1;
}

SKonto* dodajTransakcje(SKonto*& konta, int& n, const string& nr_konta, const string& imie, const string& nazwisko, int id_transakcji, const string& data, double kwota) {
    if (n < 0) {
        cerr << "Tablica nie ma elementow o indeksie:" << n << endl;
        return nullptr;
    }
    konta[n].nr_konta = nr_konta;
    konta[n].imie = imie;
    konta[n].nazwisko = nazwisko;
    konta[n].id_transakcji = id_transakcji;
    konta[n].data = data;
    konta[n].kwota = kwota;

    return konta;
}

string losuj(const int min=0, const int max=9) {
    int liczba = min + rand() % (max-min+1);
    return "455640000" + to_string(liczba);
}

void wypisz(const SKonto* konta, const int n) {
    for (int i = 0; i<n; i++) {
        cout << konta[n].nr_konta
    }
}

void usun(SKonto*& konto) {
    if (konto != nullptr) {
        delete[] konto;
        konto = nullptr;
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Blad podania argumentow, prosze podac: <plik_wej> <plik_wyj>\n";
        return -1;
    }

    SKonto* konta = nullptr, *nowe_konto = nullptr;
    int n = 0;
    if (wczytaj(argv[1], konta, n)) {
        wypisz(konta, n);
        string los = losuj();
        nowe_konto = dodajTransakcje(konta, n, los, "Kalina", "Czerwiec", 1, "2023/02/20", 123000);
        wypisz(nowe_konto, n);
        wypisz(argv[2], nowe_konto);
        string nr_konta = "4556400001";
        wypisz(argv[2], nowe_konto, n, nr_konta);
        usun(konta);
        usun(nowe_konto);
    }

    return 0;
}