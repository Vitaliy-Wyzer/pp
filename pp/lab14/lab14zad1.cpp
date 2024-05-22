#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SLista {
    struct SOsoba {
        unsigned int id;
        string email;
        unsigned int rok;
        string imie;
    };

    string nazwa_listy;
    SOsoba* osoby;
    int liczba_osob;
};

SLista::SOsoba wczytaj(ifstream& in) {
    if(!in.good()) {
        cerr << "Blad strumienia wejsciowego.\n";
        in.ignore();
        in.clear();
        in.close();
        exit(0);
    }
    SLista::SOsoba os;
    in >> os.id;
    if(!in.good()) {
        cerr << "Blad wczytywania id.\n";
        in.ignore();
        in.clear();
        in.close();
        exit(0);
    }
    in >> os.email;
    if(!in.good()) {
        cerr << "Blad wczytywania e-maila.\n";
        in.ignore();
        in.clear();
        in.close();
        exit(0);
    }
    in >> os.rok;
    if(!in.good()) {
        cerr << "Blad wczytywania roku urodzenia.\n";
        in.ignore();
        in.clear();
        in.close();
        exit(0);
    }
    in >> os.imie;
    if(!in.good()) {
        cerr << "Blad wczytywania imienia.\n";
        in.ignore();
        in.clear();
        in.close();
        exit(0);
    }
    return os;
}

bool wypisz(SLista::SOsoba& os, ostream& out = cout) {
    if(!out.good()) {
        cerr << "Blad otwarcia strumienia.\n";
        out.clear();
        return false;
    }
    out << os.id;
    if(!out.good()) {
        cerr << "Blad wypisywania id.\n";
        out.clear();
        return false;
    }
    out << " " << os.email;
    if(!out.good()) {
        cerr << "Blad wypisywania e-maila.\n";
        out.clear();
        return false;
    }
    out << " " << os.rok;
    if(!out.good()) {
        cerr << "Blad wypisywania roku urodzenia.\n";
        out.clear();
        return false;
    }
    out << " " << os.imie << endl;
    if(!out.good()) {
        cerr << "Blad wypisywania imienia.\n";
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
        l.osoby[i] = wczytaj(in);
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

SLista::SOsoba szukaj(SLista& l, const unsigned int id) {
    for(int i = 0; i < l.liczba_osob; ++i) {
        if(l.osoby[i].id == id) {
            return l.osoby[i];
        }
    }
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

void usun(SLista& l) {
    if(l.osoby) {
        delete[] l.osoby;
        l.osoby = nullptr;
    }
}

int main(int argc, char** argv) {
    if(argc != 5) {
        cerr << "Podano nieprawidlowa liczbe argumentow. Prawidlowe uzycie: ./nazwa <nazwaPlikuWejsciowego> <nazwaPlikuWyjsciowegoKobiety> <nazwaPlikuWyjsciowegoMezczyzni> <id>.\n";
        return 1;
    }
    ifstream infile(argv[1]);
    ofstream outfile_k(argv[2]);
    ofstream outfile_m(argv[3]);

    SLista lista;
    if(wczytaj(lista, infile)) {
        wypisz(lista);
        SLista::SOsoba osoba = szukaj(lista, atoi(argv[4]));
        wypisz(osoba);
        podzial(lista, outfile_k, outfile_m);
    }

    usun(lista);

    infile.close();
    outfile_k.close();
    outfile_m.close();

    return 0;
}
