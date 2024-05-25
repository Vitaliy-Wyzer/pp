#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SOsoba {
	string imie;
	unsigned int rok;
	string znak;
	int liczba;
		
	bool wczytaj(SOsoba&, ifstream&);
	bool wypisz(SOsoba&, ostream&);
};

struct SLista {
	string nazwa_listy;
	int liczba_osob;
	SOsoba* osoby;
	
	bool wczytaj(SLista&, ifstream&);
	bool wypisz(SLista&, ostream&);
	SOsoba szukaj(SLista&, const string);
	void podzial(SLista&, ofstream&, ofstream&);
	void podzial(SLista&);
	void usun() {
		if(osoby) {
			delete[] osoby;
			osoby = nullptr;
		}
	}
};

bool SOsoba::wczytaj(SOsoba& os, ifstream& fin) {
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

bool SOsoba::wypisz(SOsoba& os, ostream& out = cout) {
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

bool SLista::wczytaj(SLista& l, ifstream& fin) {
	if(!fin.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		l.usun();
		return false;
	}
	fin >> l.nazwa_listy;
	if(!fin.good()) {
		cerr << "Blad wczytywania nazwy listy.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		l.usun();
		return false;
	}
	fin >> l.liczba_osob;
	if(!fin.good()) {
		cerr << "Blad wczytywania liczby osob.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		l.usun();
		return false;
	}
	if(l.liczba_osob<=0) {
		cerr << "Liczba osob powinna byc wieksza od zera.\n";
		return false;
	}
	l.osoby = new SOsoba[l.liczba_osob];
	for(int i=0; i<l.liczba_osob; ++i) {
		if(!(l.osoby[i].wczytaj(l.osoby[i], fin))) {
			cerr << "Wystapil blad podczas wczytywania danych " << i << ". osoby.\n";
			fin.ignore();
			fin.clear();
			fin.close();
			l.usun();
			return false;
		}
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

SOsoba SLista::szukaj(SLista& l, const string znak) {
	SOsoba os = {"", 0, "", 0};
	for(int i=0; i<l.liczba_osob; ++i) {
		if(l.osoby[i].znak==znak) {
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

void SLista::podzial(SLista& l) {
	for(int i=0; i<l.liczba_osob; ++i)
		if(l.osoby[i].liczba%2==0)
			l.osoby[i].wypisz(l.osoby[i]);
}

int main(int argc, char** argv) {
	if(argc!=5) {
		cerr << "Niepoprawna liczba parametrow uruchomienia programu. Prawidlowe uzycie: ./nazwa <nazwaPlikuWejsciowego> <nazwaPlikuWyjsciowegoKobiety> <nazwaPlikuWyjsciowegoMezczyzni> <szukanyZnakZodiaku>.\n";
		return 1;
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
		return 5;
	}
	
	SLista lista;
	SOsoba osoba;
	if(lista.wczytaj(lista, in)) {
		lista.wypisz(lista);
		osoba = lista.szukaj(lista, argv[4]);
		if(osoba.znak!="") {
			cout << "\nZnaleziono osobe o podanym znaku zodiaku:\n";
			if(!osoba.wypisz(osoba)) {
				cerr << "Napotkano blad podczas wypisywania danych osoby.\n";
				lista.usun();
				return 2;
			}
			lista.podzial(lista, out_k, out_m);
		} else {
			cerr << "Nie znaleziono osoby o podanym znaku zodiaku.\n";
			lista.usun();
			return 3;
		}
		lista.usun();
	} else {
		cerr << "Nastapil blad podczas wczytywania listy.\n";
		in.ignore();
		in.clear();
		in.close();
		lista.usun();
		return 4;
	}
	
	lista.usun();
	
	in.close();
	out_k.close();
	out_m.close();

	return 0;
}
