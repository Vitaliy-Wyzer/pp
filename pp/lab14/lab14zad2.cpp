#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SLista {
    struct SOsoba {
        string imie;
        int rok;
        string znak;
        int liczba;
    };

    string nazwa_listy;
    SOsoba* osoby;
    int liczba_osob;
};

bool wczytaj(SLista::SOsoba& os, ifstream& fin) {
    if(!fin.good()) {
        cerr << "Blad strumienia wejsciowego.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> os.imie;
    if(!fin.good()) {
        cerr << "Blad wczytywania imienia.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> os.rok;
    if(!fin.good()) {
        cerr << "Blad wczytywania roku urodzenia.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> os.znak;
    if(!fin.good()) {
        cerr << "Blad wczytywania znaku zodiaku.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> os.liczba;
    if(!fin.good()) {
        cerr << "Blad wczytywania szczesliwej liczby.\n";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    return true;
}

bool wypisz(SLista::SOsoba& os, ostream& out = cout) {
    if(!out.good()) {
        cerr << "Blad strumienia wyjsciowego.\n";
        out.clear();
        return false;
    }
    out << os.imie;
    if(!out.good()) {
        cerr << "Blad wypisywania imienia.\n";
        out.clear();
        return false;
    }
    out << '\t' << os.rok;
    if(!out.good()) {
        cerr << "Blad wypisywania roku urodzenia.\n";
        out.clear();
        return false;
    }
    out << '\t' << os.znak;
    if(!out.good()) {
        cerr << "Blad wypisywania znaku zodiaku.\n";
        out.clear();
        return false;
    }
    out << '\t' << os.liczba << endl;
    if(!out.good()) {
        cerr << "Blad wypisywania szczesliwej liczby.\n";
        out.clear();
        return false;
    }
    return true;
}

bool wczytaj(SLista& l, ifstream& in) {
    if(!in.good()) {
        cerr << "Blad otwarcia pliku wejsciowego.\n";
        in.ignore();
        in.clear();
        in.close();
        return false;
    }
    in >> l.nazwa_listy;
    if(!in.good()) {
        cerr << "Blad wczytywania nazwy listy.\n";
        in.ignore();
        in.clear();
        in.close();
        return false;
    }
    in >> l.liczba_osob;
    if(!in.good()) {
        cerr << "Blad wczytywania liczby osob.\n";
        in.ignore();
        in.clear();
        in.close();
        return false;
    }
    l.osoby = new SLista::SOsoba[l.liczba_osob];
    for(int i = 0; i < l.liczba_osob; ++i) {
        wczytaj(l.osoby[i], in);
    }

    return true;
}

bool wypisz(SLista& l, ostream& out = cout) {
    if(!out.good()) {
        cerr << "Blad strumienia.\n";
        out.clear();
        return false;
    }
    out << l.nazwa_listy << endl;
    if(!out.good()) {
        cerr << "Blad wypisywania nazwy listy.\n";
        out.clear();
        return false;
    }
    out << l.liczba_osob << endl;
    if(!out.good()) {
        cerr << "Blad wypisywania liczby osob.\n";
        out.clear();
        return false;
    }
    for(int i = 0; i < l.liczba_osob; ++i) {
        if(!wypisz(l.osoby[i], out)) {
            cerr << "Blad wypisywania " << i + 1 << ". osoby.\n";
            return false;
        }
    }
    return true;
}

SLista::SOsoba szukaj(SLista& l, const string zodiak) {
    for(int i = 0; i < l.liczba_osob; ++i) {
        if(l.osoby[i].znak == zodiak) {
            return l.osoby[i];
        }
    }
    cerr << "Nie znaleziono osoby o podanym znaku zodiaku.\n";
    exit(0);
}

void podzial(SLista& l, ofstream& plik_k, ofstream& plik_m) {
    for(int i = 0; i < l.liczba_osob; ++i) {
        if(l.osoby[i].imie.back() == 'a' || l.osoby[i].imie.back() == 'A') {
            if(!wypisz(l.osoby[i], plik_k)) {
                cerr << "Napotkano blad.\n";
                exit(0);
            }
        } else {
            if(!wypisz(l.osoby[i], plik_m)) {
                cerr << "Napotkano blad.\n";
                exit(0);
            }
        }
    }
}

void podzial(SLista& l) {
    for(int i = 0; i < l.liczba_osob; ++i) {
        if(l.osoby[i].liczba % 2 == 0) {
            if(!wypisz(l.osoby[i])) {
                cerr << "Napotkano blad.\n";
                exit(0);
            }
        }
    }
}

void usun(SLista& l) {
    if(l.osoby) {
        delete[] l.osoby;
        l.osoby = nullptr;
    }
}

int main(int argc, char** argv) {
    if(argc != 5) {
        cerr << "Podano nieprawidlowa liczbe argumentow. Prawidlowe uzycie: ./nazwa <nazwaPlikuWejsciowego> <nazwaPlikuWyjsciowegoKobiety> <nazwaPlikuWyjsciowegoMezczyzni> <znakZodiaku>.\n";
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile_k(argv[2]);
    ofstream outfile_m(argv[3]);

    SLista lista;
    if(wczytaj(lista, infile)) {
        wypisz(lista);
        SLista::SOsoba osoba = szukaj(lista, argv[4]);
        wypisz(osoba);
        podzial(lista, outfile_k, outfile_m);
    }

    podzial(lista);

    usun(lista);

    infile.close();
    outfile_k.close();
    outfile_m.close();

    return 0;
}
