#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SProstopadloscian {
    float dlugosc;
    float szerokosc;
    float wysokosc;
};

SProstopadloscian* wczytaj(const char* plik_wej, int& n) {
    ifstream plik(plik_wej);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku." << endl;
        return nullptr;
    }
    plik >> n;
    SProstopadloscian* prostopadlosciane = new SProstopadloscian[n];
    for (int i = 0; i < n; ++i) {
        plik >> prostopadlosciane[i].dlugosc >> prostopadlosciane[i].szerokosc >> prostopadlosciane[i].wysokosc;
    }
    plik.close();
    return prostopadlosciane;
}

float pole(const SProstopadloscian& p) {
    return 2 * (p.dlugosc * p.szerokosc + p.dlugosc * p.wysokosc + p.szerokosc * p.wysokosc);
}

int znajdz_pole(const SProstopadloscian* p, const int n) {
    int indeks_max = 0;
    float max_pole = pole(p[0]);
    for (int i = 1; i < n; ++i) {
        float aktualne_pole = pole(p[i]);
        if (aktualne_pole > max_pole) {
            max_pole = aktualne_pole;
            indeks_max = i;
        }
    }
    return indeks_max;
}

float objetosc(const SProstopadloscian& p) {
    return p.dlugosc * p.szerokosc * p.wysokosc;
}

float znajdz_objetosc(const SProstopadloscian* p, const int n) {
    float max_objetosc = objetosc(p[0]);
    for (int i = 1; i < n; ++i) {
        float aktualna_objetosc = objetosc(p[i]);
        if (aktualna_objetosc > max_objetosc) {
            max_objetosc = aktualna_objetosc;
        }
    }
    return max_objetosc;
}

bool wysokosc(const SProstopadloscian& p1, const SProstopadloscian& p2) {
    return p1.wysokosc > p2.wysokosc;
}

void sortuj(SProstopadloscian* p, const int n, bool (*wfun)(const SProstopadloscian&, const SProstopadloscian&)) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (wfun(p[j], p[j + 1])) {
                SProstopadloscian temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void wypisz(const SProstopadloscian* p) {
    cout << "Dlugosc\tSzerokosc\tWysokosc" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << p[i].dlugosc << "\t" << p[i].szerokosc << "\t" << p[i].wysokosc << endl;
    }
}

void wypisz(const SProstopadloscian* p, const int n) {
    cout << "Dlugosc\tSzerokosc\tWysokosc" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << p[i].dlugosc << "\t" << p[i].szerokosc << "\t" << p[i].wysokosc << endl;
    }
}

bool wypisz(const SProstopadloscian& p, ofstream& fout) {
    fout << p.dlugosc << "\t" << p.szerokosc << "\t" << p.wysokosc << endl;
    return 1;
}

bool wypisz(const SProstopadloscian* p, const int n, const string& plik_wyj) {
    ofstream fout(plik_wyj, ios_base::app);
    if (!fout.good()) {
        cerr << "Nie mozna otworzyc pliku." << endl;
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (!wypisz(p[i], fout)) {
            return false;
        }
    }
    fout << "\n";

    fout.clear();
    fout.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uzycie: " << argv[0] << " <plik_wejsciowy> <plik_wyjsciowy>" << endl;
        return 1;
    }
    int n = 0;
    SProstopadloscian* p = wczytaj(argv[1], n);
    if (p) {
        wypisz(p);
        if (wypisz(p, n, argv[2])) {
            cout << "Zapisano pomyslnie do pliku." << endl;
        } else {
            cerr << "Cos poszlo nie tak!" << endl;
        }
        cout << "Prostopadloscian o najwiekszym polu powierzchni znajduje sie na pozycji: " << znajdz_pole(p, n) << endl;
        cout << "Najwieksza objetosc prostopadloscianu wynosi: " << znajdz_objetosc(p, n) << endl;
        sortuj(p, n, wysokosc);
        cout << "Posortowane wzgledem wysokosci prostopadlosciany:" << endl;
        wypisz(p, n);
        if (wypisz(p, n, argv[2])) {
            cout << "Zapisano pomyslnie do pliku." << endl;
        } else {
            cerr << "Cos poszlo nie tak!" << endl;
        }
        delete[] p;
    } else {
        cerr << "Blad podczas wczytywania danych." << endl;
    }
    return 0;
}
