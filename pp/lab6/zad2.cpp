#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// писав джпт, підкореговано під код Зих
void zapisz(const string& plik_wyj, const string& zawartosc, const unsigned ile) {
    ofstream plik(plik_wyj, ios::app);
    if (plik.is_open()) {
        for (unsigned i = 0; i<ile; i++) {
            plik << zawartosc << endl;
        }
        plik.clear();
        plik.close();
    } else {
        cerr << "Blad otwarcia pliku wyjsciowego" << endl;
        plik.clear();
        plik.close();
    }
}

// точна копія коду Зих
void zapisz(ofstream& fout, const string zawartosc, const unsigned ile = 10) {
    for (unsigned i = 0; i<ile; i++) {
        fout << zawartosc << endl;
        if (!fout.good()) {
            cerr << "Blad otwarcia pliku wyjsciowego" << endl;
            fout.clear();
            fout.close();
        }
    }
}


// код Зих підкорегований під першу функцію
int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Za malo parametrow uruchomienia programu" << endl;
        cerr << "./program plik_wyj napis liczba" << endl;
        return -1;
    }

    const string nazwa_pliku = argv[1];
    const string napis = argv[2];
    const unsigned n = atoi(argv[3]);
    zapisz(nazwa_pliku, napis, n);

    ofstream fout(nazwa_pliku, ios::app);
    if (!fout.good()) {
        cerr << "Blad otwarcia pliku wyjsciowego" << endl;
        fout.clear();
        fout.close();
        return -1;
    }
    fout << endl;
    fout << "*** dopisane ***" << endl;
    zapisz(fout, napis);

    fout.clear();
    fout.close();
}