#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SOsoba {
    string imie, znak_zodiaku;
    unsigned int rok, szesliwa_liczba;

    SOsoba(): imie(""), rok(0), znak_zodiaku(""), szesliwa_liczba(0) {}

    bool wczytaj(SOsoba&, ifstream&);
    bool wypisz(SOsoba&, ostream& out = cout);
};

struct SLista {
    string nazwa;
    unsigned int liczba;
    SOsoba* osoby;

    SLista(): nazwa(""), liczba(0), osoby(nullptr) {}

    bool wczytaj(SLista&, ifstream&);
    bool wypisz(SLista&, ostream& out = cout);
    SOsoba szukaj(SLista&, const string);
    void podzial(SLista&, ofstream&, ofstream&);
    void podzial(SLista&);

    ~SLista() {
        if (osoby) {
            delete[] osoby;
            osoby = nullptr;
        }
    }
};

bool SOsoba::wczytaj(SOsoba& osoba, ifstream& fin) {
    if(!fin.good()) {
        cerr << "Blad otwierania pliku wejsciowego.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if(!(fin >> osoba.imie)) {
        cerr << "Blad wczytywania imienia.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if(!(fin >> osoba.rok)) {
        cerr << "Blad wczytywania roku urodzenia.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if(!(fin >> osoba.znak_zodiaku)) {
        cerr << "Blad wczytywania znaku zodiaka\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if(!(fin >> osoba.szesliwa_liczba)) {
        cerr << "Blad wczytywania liczby szesliwej.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    return 1;
}

bool SOsoba::wypisz(SOsoba& osoba, ostream& out) {
    out << osoba.imie << "\t";
    if (!out.good()) {
        cerr << "Blad wypisywania imienia.\n";
        out.clear();
        return 0;
    }
    out << osoba.rok << "\t";
    if (!out.good()) {
        cerr << "Blad wypisywania roku urodzenia.\n";
        out.clear();
        return 0;
    }
    out << osoba.znak_zodiaku << "\t";
    if (!out.good()) {
        cerr << "Blad wypisywania znaku zodiaku.\n";
        out.clear();
        return 0;
    }
    out << osoba.szesliwa_liczba << "\t";
    if (!out.good()) {
        cerr << "Blad wypisywania liczby szesliwej.\n";
        out.clear();
        return 0;
    }
    return 1;
}

bool SLista::wczytaj(SLista& lista, ifstream& fin) {
    if (!fin.good()) {
        cerr << "Blad otwarcia pliku wejsciowego.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if (!(fin >> lista.nazwa)) {
        cerr << "Blad wczytywania nazwy listy.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if (!(fin >> lista.liczba)) {
        cerr << "Blad wczytywania liczby osob.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    if (lista.liczba < 0) {
        cerr << "Liczba osob musi byc dodatnia.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return 0;
    }
    lista.osoby = new SOsoba[lista.liczba];
    for (unsigned int i=0; i<lista.liczba; i++) {
        if(lista.osoby[i].wczytaj(lista.osoby[i], fin));
            cerr << "Blad wczytywania do listy osob.\n";
            fin.ignore();
            fin.clear();
            fin.close();
            return 0;
    }
    return 1;
}

bool SLista::wypisz(SLista& lista, ostream& out) {
    out << lista.nazwa << "\n";
    if (!out.good()) {
        cerr << "Blad wypisywania nazwy listy.\n";
        out.clear();
        return 0;
    }
    out << lista.liczba << "\n";
    if (!out.good()) {
        cerr << "Blad wypisywania liczby osob.\n";
        out.clear();
        return 0;
    }
    for (unsigned int i=0; i<lista.liczba; i++) {
        if (!lista.osoby[i].wypisz(lista.osoby[i]), out) {
            cerr << "Blad wypisywania z listy osob.\n";
            return 0;
        }
    }
    return 0;
}

SOsoba SLista::szukaj(SLista& lista, const string znak) {
    SOsoba osoba;
    for (unsigned int i=0; i<lista.liczba; i++) {
        if (lista.osoby[i].znak_zodiaku == znak) {
            return lista.osoby[i];
        }
    }
    return osoba;
}

void SLista::podzial(SLista& lista, ofstream& kob, ofstream& mez) {
    if (!(kob.good() && mez.good())) {
        cerr << "Blad plikow wyjsciowych.\n";
        kob.clear();
        kob.close();
        mez.clear();
        mez.close();
    } else {
        for (unsigned int i=0; i<lista.liczba; i++) {
            if (lista.osoby[i].imie.back() == 'a') {
                lista.osoby[i].wypisz(lista.osoby[i], kob);
            } else {
                lista.osoby[i].wypisz(lista.osoby[i], mez);
            }
        }
    }
}

void SLista::podzial(SLista& lista) {
    cout << "Osoby z parzysta liczba szesliwa:\n";
    for (unsigned int i=0; i<lista.liczba; i++) {
        if (lista.osoby[i].szesliwa_liczba % 2 == 0) {
            lista.osoby[i].wypisz(lista.osoby[i]);
        }
    }
}

int main(int argc, char** argv) {
    if (argc !=5) {
        cerr << "Prosze podac 4 argumenty: <input.txt> <out_kobiety.txt> <out_mezczyzni.txt> <znak zodiaku>\n";
        return -1;
    }

    ifstream fin(argv[1]);
    ofstream kob(argv[2]);
    ofstream mez(argv[3]);

    if (!(fin.good() && kob.good() && mez.good())) {
        cerr << "Blad strumienia plikowego.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        kob.clear();
        kob.close();
        mez.clear();
        mez.close();
        return -1;
    }

    SLista lista;

    if (lista.wczytaj(lista, fin)) {
        if (lista.wypisz(lista)) {
            SOsoba osoba;
            osoba = lista.szukaj(lista, argv[4]);
            if (osoba.imie=="" && osoba.rok==0 && osoba.znak_zodiaku=="" && osoba.szesliwa_liczba==0) {
                cout << "Nie znaleziono osoby o podanym znaku zodiaku.\n";
            } else {
                cout << "Znaleziono osobe o podanym znaku zodiaku:\n";
                if(!osoba.wypisz(osoba)) {
                    cerr << "Blad wypisywania osoby o podanym znaku zodiaku.\n";
                    return -1;
                }
            }

        }
        lista.podzial(lista, kob, mez);
        lista.podzial(lista);
    } else {
        cerr << "Blad wczytywania z pliku.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return -1;
    }

    fin.close();
    kob.close();
    mez.close();

    return 0;
}
