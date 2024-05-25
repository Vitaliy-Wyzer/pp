#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

// Author: Sigma

using namespace std;

struct SNKurs {
	string nazwa_kursu;
};

struct SStudent {
	string imie, nazwisko;
	unsigned int liczba_nkursow;
	SNKurs* nkursy;
		
	bool wczytaj(SStudent&, ifstream&);
	bool wypisz(SStudent&, ostream&);
	void usun() {
		if(nkursy) {
			delete[] nkursy;
			nkursy = nullptr;
		}
	}
};

struct SLista {
	string nazwa_listy;
	int liczba_studentow;
	SStudent* studenci;
	
	bool wczytaj(SLista&, ifstream&);
	bool wypisz(SLista&, ostream&);
	double srednia(const SLista&);
	SStudent maksymalna(SLista&);
	void usun() {
		if(studenci) {
			delete[] studenci;
			studenci = nullptr;
		}
	}
};

bool SStudent::wczytaj(SStudent& st, ifstream& fin) {
	st.nkursy = nullptr;
	if(!fin.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> st.imie;
	if(!fin.good()) {
		cerr << "Blad wczytywania imienia.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> st.nazwisko;
	if(!fin.good()) {
		cerr << "Blad wczytywania nazwiska.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> st.liczba_nkursow;
	if(!fin.good()) {
		cerr << "Blad wczytywania liczby niezaliczonych kursow.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	if(st.liczba_nkursow<0) {
		cerr << "Liczba niezalicznonych kursow powinna byc nieujemna.\n";
		return false;
	}
	st.nkursy = new SNKurs[st.liczba_nkursow];
	for(unsigned int i=0; i<st.liczba_nkursow; ++i) {
		fin >> st.nkursy[i].nazwa_kursu;
		if(!fin.good()) {
			cerr << "Blad wczytywania " << i << ". niezaliczonego kursu.\n";
			fin.ignore();
			fin.clear();
			fin.close();
			st.usun();
			return false;
		}
	}
	return true;
}

bool SStudent::wypisz(SStudent& st, ostream& out = cout) {
	if(!out.good()) {
		cerr << "Blad strumienia wyjsciowego.\n";
		out.clear();
		return false;
	}
	out << st.imie;
	if(!out.good()) {
		cerr << "Blad wypisywania imienia.\n";
		out.clear();
		return false;
	}
	out << '\t' << st.nazwisko;
	if(!out.good()) {
		cerr << "Blad wypisywania nazwiska.\n";
		out.clear();
		return false;
	}
	out << '\t' << st.liczba_nkursow;
	if(!out.good()) {
		cerr << "Blad wypisywania liczby niezaliczonych kursow.\n";
		out.clear();
		return false;
	}
	for(unsigned int i=0; i<st.liczba_nkursow; ++i) {
		out << '\t' << st.nkursy[i].nazwa_kursu;
		if(!out.good()) {
			cerr << "Blad wypisywania " << i << ". niezaliczonego nkursu.\n";
			out.clear();
			return false;
		}
	}
	out << endl;
	return true;
}

bool SLista::wczytaj(SLista& l, ifstream& fin) {
	l.studenci = nullptr;
	if(!fin.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> l.nazwa_listy;
	if(!fin.good()) {
		cerr << "Blad wczytywania nazwy listy.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> l.liczba_studentow;
	if(!fin.good()) {
		cerr << "Blad wczytywania liczby studentow.\n";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	if(l.liczba_studentow<=0) {
		cerr << "Liczba studentow powinna byc wieksza od zera.\n";
		return false;
	}
	l.studenci = new SStudent[l.liczba_studentow];
	for(int i=0; i<l.liczba_studentow; ++i) {
		l.studenci[i].nkursy = nullptr;
		if(!(l.studenci[i].wczytaj(l.studenci[i], fin))) {
			cerr << "Wystapil blad podczas wczytywania danych " << i << ". studenta.\n";
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
	out << l.liczba_studentow << endl;
	if(!out.good()) {
		cerr << "Blad wypisywania liczby studentow.\n";
		out.clear();
		return false;
	}
	for(int i=0; i<l.liczba_studentow; ++i) {
		if(!(l.studenci[i].wypisz(l.studenci[i], out))) {
			cerr << "Napotkano blad.\n";
			out.clear();
			return false;
		}
	}
	return true;
}

double SLista::srednia(const SLista& l) {
	unsigned int suma = 0;
	for(int i=0; i<l.liczba_studentow; ++i) {
		suma += l.studenci[i].liczba_nkursow;
	}
	return (double(suma)/double(l.liczba_studentow));
}

SStudent SLista::maksymalna(SLista& l) {
	unsigned int max = l.studenci[0].liczba_nkursow;
	int index = 0;
	for(int i=1; i<l.liczba_studentow; ++i) {
		if(l.studenci[i].liczba_nkursow > max) {
			max = l.studenci[i].liczba_nkursow;
			index = i;
		}
	}
	return l.studenci[index];
}

int main(int argc, char** argv) {
	if(argc!=2) {
		cerr << "Niepoprawna liczba parametrow uruchomienia programu. Prawidlowe uzycie: ./nazwa <nazwaPlikuWejsciowego>.\n";
		return 1;
	}
	
	ifstream in(argv[1]);
	
	if(!in.good()) {
		cerr << "Blad strumienia wejsciowego.\n";
		in.ignore();
		in.clear();
		in.close();
		return 2;
	}
	
	SLista lista = {"", 0};
	
	if(lista.wczytaj(lista, in)) {
		lista.wypisz(lista);
		SStudent student = lista.maksymalna(lista);
			cout << "\nZnaleziono studenta z najwieksza liczba niezaliczonych kursow:\n";
			if(!student.wypisz(student)) {
				cerr << "Napotkano blad podczas wypisywania danych studenta z najwieksza liczba niezaliczonych kursow.\n";
				student.usun();
				lista.usun();
				return 3;
			}
	} else {
		cerr << "Nastapil blad podczas wczytywania listy.\n";
		in.ignore();
		in.clear();
		in.close();
		lista.usun();
		return 4;
	}
	
	double sr = lista.srednia(lista);
	cout << "Srednia liczba niezaliczonych kursow wsrod studentow znajdujacych sie na liscie:\n" << sr << '\n';
	
	for(int i=0; i<lista.liczba_studentow; ++i) {
		lista.studenci[i].usun();
	}
	lista.usun();
	in.close();

	return 0;
}
