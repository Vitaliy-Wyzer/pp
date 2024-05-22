#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct SOsoba {
	unsigned int id;
	string email;
	unsigned rok;
	string imie;
	
	SOsoba() : id(0), email(""), rok(0), imie("") {}
	
	SOsoba wczytaj(ifstream&);
	bool wypisz(SOsoba&, ostream&);
};

struct SLista {
	string nazwa;
	unsigned int liczba;
	SOsoba* osoby;
	
	SLista() : nazwa(""), liczba(0), osoby(nullptr) {}
	
	bool wczytaj(SLista&, ifstream&);
	bool wypisz(SLista&, ostream&);
	SOsoba szukaj(SLista&, const unsigned int);
	void podzial(SLista&, ofstream&, ofstream&);
};

SOsoba SOsoba::wczytaj(ifstream& fin) {
	SOsoba osoba;
	if (!fin.good()) {
		cerr << "Blad otwarcia pliku wejsciowego\n";
		fin.ignore();
		fin.clear();
		fin.close();
		exit(0);
	}
	
	fin >> osoba.id;
	if(!fin.good()) {
		cerr << "Blad wczytywania id\n";
		fin.ignore();
		fin.clear();
		fin.close();
		exit(0);
	}
	fin >> osoba.email;
	if(!fin.good()) {
		cerr << "Blad wczytywania emailu\n";
		fin.ignore();
		fin.clear();
		fin.close();
		exit(0);
	}
	fin >> osoba.rok;
	if(!fin.good()) {
		cerr << "Blad wczytywania roku urodzenia\n";
		fin.ignore();
		fin.clear();
		fin.close();
		exit(0);
	}
	fin >> osoba.imie;
	if(!fin.good()) {
		cerr << "Blad wczytywania imienia\n";
		fin.ignore();
		fin.clear();
		fin.close();
		exit(0);
	}
	return osoba;
}

bool SOsoba::wypisz(SOsoba& osoba, ostream& out = cout) {
	if (!out.good()) {
		cerr << "Blad otwarcia pliku wyjsciowego\n";
		out.clear();
		return 0;
	}
	if (!(out << osoba.id << " ")) {
		cerr << "Blad wypisania id\n";
		out.clear();
		return 0;
	}
	if (!(out << osoba.email << " ")) {
		cerr << "Blad wypisania email\n";
		out.clear();
		return 0;
	}
	if (!(out << osoba.rok << " ")) {
		cerr << "Blad wypisania roku urodzenia\n";
		out.clear();
		return 0;
	}
	if (!(out << osoba.imie << endl)) {
		cerr << "Blad wypisania imienia\n";
		out.clear();
		return 0;
	}
	return 1;
}

bool SLista::wczytaj(SLista& lista, ifstream& fin) {
	if (!fin.good()) {
		cerr << "Blad otwarcia pliku wejsciowego\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return 0;
	}
	fin >> lista.nazwa;
	if (!fin.good()) {
		cerr << "Blad wczytywania nazwy\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return 0;
	}
	fin >> lista.liczba;
	if (!fin.good()) {
		cerr << "Blad wczytywania liczby osob\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return 0;
	}
	if (0 >= lista.liczba) {
		cerr << "Libcza osob musi byc >= 1\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return 0;
	}
	lista.osoby = new SOsoba[lista.liczba];
	for (unsigned int i=0; i<lista.liczba; i++) {
		lista.osoby[i] = lista.osoby[i].wczytaj(fin);
		if (lista.osoby[i].id == 0 || lista.osoby[i].email == "" ||
			lista.osoby[i].rok == 0 || lista.osoby[i].imie == "") {
			cerr << "Blad wczytywania danych z pliku\n";
			fin.ignore();
			fin.clear();
			fin.close();
			return 0;	
		}
	}

	return 1;
}

bool SLista::wypisz(SLista& lista, ostream& out = cout) {
      if(!out.good()) {
            cerr << "Blad strumienia.\n";
            out.clear();
            return false;
        }
        out << lista.nazwa << endl;
        if(!out.good()) {
            cerr << "Blad wypisywania nazwy listy.\n";
            out.clear();
            return false;
        }
        out << lista.liczba << endl;
        if(!out.good()) {
            cerr << "Blad wypisywania liczby osob.\n";
            out.clear();
            return false;
        }
        for(unsigned int i=0; i<lista.liczba; ++i) {
            if(!lista.osoby[i].wypisz(lista.osoby[i], out)) {
                cerr << "Blad wypisywania " << i + 1 << ". osoby.\n";
                return false;
            }
        }
        return true;
}

SOsoba SLista::szukaj(SLista& lista, const unsigned int id) {
	for(unsigned int i=0; i<lista.liczba; ++i) {
		if(lista.osoby[i].id == id) {
			return lista.osoby[i];
        }
    }
	exit(0);
}

void SLista::podzial(SLista& lista, ofstream& fout1, ofstream& fout2) {
	for(unsigned int i=0; i<lista.liczba; ++i) {
		if(lista.osoby[i].imie.back() == 'a') {
			if(!lista.osoby[i].wypisz(lista.osoby[i], fout1)) {
				cerr << "Blad\n";
                exit(0);
            }
        } else {
            if(!lista.osoby[i].wypisz(lista.osoby[i], fout2)) {
                cerr << "Blad\n";
                exit(0);
            }
        }
    }
}

void usun(SLista& lista) {
	if (lista.osoby != nullptr) {
		delete [] lista.osoby;
		lista.osoby = nullptr;
	}
}

int main(int argc, char** argv) {
	// plik wej, plik wyj, plik wyj m, plik wyj f, id
	if (argc != 5) {
		cerr << "Prosze podac argumenty: <plik wej> <plik wyj k> <plik wyj m>\n";
		return -1;
	}
	
	ifstream fin(argv[1]);
    ofstream fout_k(argv[2]);
    ofstream fout_m(argv[3]);
    
    if (!(fin.good() || fout_k.good() || fout_m.good())) {
		cerr << "Blad otwarcia plikow\n";
		fin.ignore();
		fin.clear();
		fout_k.clear();
		fout_m.clear();
		fin.close();
		fout_k.close();
		fout_m.close();
		return -1;
	}

    SLista lista;
    if(lista.wczytaj(lista, fin)) {
        lista.wypisz(lista);
        SOsoba osoba = lista.szukaj(lista, atoi(argv[4]));
        if(osoba.id!=0) { 
            lista.osoby[0].wypisz(osoba);
            lista.podzial(lista, fout_k, fout_m);
        } else {
            cerr << "Nie znaleziono osoby o podanym id.\n";
            return 1;
        }
    }

    usun(lista);

    fin.close();
    fout_k.close();
    fout_m.close();

    return 0;
}
