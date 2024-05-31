#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

// Author: Sigma

using namespace std;

struct SOsoba {
	unsigned int id;
	string email;
	unsigned int rok;
	string imie;

	SOsoba(): id(0), email(""), rok(0), imie("") {}
		
	SOsoba wczytaj(ifstream&);
	bool wypisz(SOsoba&, ostream&);
	void usun(SOsoba&);
};

struct SLista {
	string nazwa_listy;
	int liczba_osob;
	SOsoba* osoby;
	
	bool wczytaj(SLista&, ifstream&);
	bool wypisz(SLista&, ostream&);
	SOsoba szukaj(SLista&, const unsigned int);
	void podzial(SLista&, ofstream&, ofstream&);
	// void usun
	void usun() {
		if(osoby) {
			delete[] osoby;
			osoby = nullptr;
		}
	}
};

SOsoba SOsoba::wczytaj(ifstream& fin) {
	SOsoba os = SOsoba();
	if(!fin.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return os;
	}
	fin >> os.id;
	if(!fin.good()) {
		cerr << "Blad wczytywania id.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return os;
	}
	fin >> os.email;
	if(!fin.good()) {
		cerr << "Blad wczytywania adresu e-mail.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return os;
	}
	fin >> os.rok;
	if(!fin.good()) {
		cerr << "Blad wczytywania roku urodzenia.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return os;
	}
	fin >> os.imie;
	if(!fin.good()) {
		cerr << "Blad wczytywania imienia.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return os;
	}
	return os;
}

bool SOsoba::wypisz(SOsoba& os, ostream& out = cout) {
	if(!out.good()) {
		cerr << "Blad strumienia wyjsciowego.\n";
		out.clear();
		return false;
	}
	out << os.id;
	if(!out.good()) {
		cerr << "Blad wypisywania id.\n";
		out.clear();
		return false;
	}
	out << '\t' << os.email;
	if(!out.good()) {
		cerr << "Blad wypisywania adresu e-mail.\n";
		out.clear();
		return false;
	}
	out << '\t' << os.rok;
	if(!out.good()) {
		cerr << "Blad wypisywania roku urodzenia.\n";
		out.clear();
		return false;
	}
	out << '\t' << os.imie << endl;
	if(!out.good()) {
		cerr << "Blad wypisywania imienia.\n";
		out.clear();
		return false;
	}
	return true;
}

bool SLista::wczytaj(SLista& l, ifstream& fin) {
	if(!fin.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		// usun
		l.usun();
		return false;
	}
	fin >> l.nazwa_listy;
	if(!fin.good()) {
		cerr << "Blad wczytywania nazwy listy.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		// usun
		l.usun();
		return false;
	}
	fin >> l.liczba_osob;
	if(!fin.good()) {
		cerr << "Blad wczytywania liczby osob.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		// usun
		l.usun();
		return false;
	}
	if(l.liczba_osob<=0) {
		cerr << "Liczba osob powinna byc wieksza od zera.\n";
		return false;
	}
	l.osoby = new SOsoba[l.liczba_osob];
	for(int i=0; i<l.liczba_osob; ++i) {
		// no debug?
		l.osoby[i] = l.osoby[i].wczytaj(fin);
	}
	return true;
}

bool SLista::wypisz(SLista& l, ostream& out = cout) {
	if(!out.good()) {
		cerr << "Blad strumienia wyjsciowego.\n";
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
	for(int i=0; i<l.liczba_osob; ++i) {
		if(!(l.osoby[i].wypisz(l.osoby[i], out))) {
			cerr << "Napotkano blad.\n";
			out.clear();
			return false;
		}
	}
	return true;
}

SOsoba SLista::szukaj(SLista& l, const unsigned int id) {
	SOsoba os = SOsoba();
	for(int i=0; i<l.liczba_osob; ++i) {
		if(l.osoby[i].id==id) {
			return l.osoby[i];
		}
	}
	return os;
}

void SLista::podzial(SLista& l, ofstream& fout_k, ofstream& fout_m) {
	if(!(fout_k.good() && fout_m.good())) {
		cerr << "Blad strumieni wyjsciowych.\n";
		fout_k.clear();
		fout_k.close();
		fout_m.clear();
		fout_m.close();
		exit(0);
	}
	for(int i=0; i<l.liczba_osob; ++i) {
		if(l.osoby[i].imie.back()=='a') {
			if(!(l.osoby[i].wypisz(l.osoby[i], fout_k))) {
				cerr << "Napotkano blad.\n";
				fout_k.clear();
				fout_k.close();
				exit(0);
			}
		} else {
			if(!(l.osoby[i].wypisz(l.osoby[i], fout_m))) {
				cerr << "Napotkano blad.\n";
				fout_m.clear();
				fout_m.close();
				exit(0);
			}
		}
	}
}

int main(int argc, char** argv) {
	if(argc!=5) {
		cerr << "Niepoprawna liczba parametrow uruchomienia programu. Prawidlowe uzycie: ./nazwa <nazwaPlikuWejsciowego> <nazwaPlikuWyjsciowegoKobiety> <nazwaPlikuWyjsciowegoMezczyzni> <szukaneId>.\n";
		return -1;
	}
	
	ifstream in(argv[1]);
	ofstream out_k(argv[2]);
	ofstream out_m(argv[3]);
	
	if(!(in.good() && out_k.good() && out_m.good())) {
		cerr << "Blad strumieni.\n";
		in.ignore();
		in.clear();
		in.close();
		out_k.clear();
		out_k.close();
		out_m.clear();
		out_m.close();
		return -1;
	}
	
	SLista lista;
	SOsoba osoba;
	if(lista.wczytaj(lista, in)) {
		lista.wypisz(lista);
		osoba = lista.szukaj(lista, atoi(argv[4]));
		if(osoba.id!=0) {
			cout << "\nZnaleziono osobe o podanym id:\n";
			// debug
			if(!osoba.wypisz(osoba)) {
				cerr << "Napotkano blad podczas wypisywania danych osoby.\n";
				lista.usun();
				return -1;
			}
			lista.podzial(lista, out_k, out_m);
		} else {
			cerr << "Nie znaleziono osoby o podanym id.\n";
			// usun
			lista.usun();
			return -1;
		}
		// usun
		lista.usun();
	} else {
		// debug
		cerr << "Nastapil blad podczas wczytywania listy.\n";
		in.ignore();
		in.clear();
		in.close();
		lista.usun();
		return -1;
	}
	
	lista.usun();
	
	in.close();
	out_k.close();
	out_m.close();

	return 0;
}
