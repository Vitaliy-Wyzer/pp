// Tkachenko Vladyslav Gr. 6

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;



struct SAutor{
	string imie;
	string nazwisko;
	char typ;
	unsigned int liczba;
	string* ksiazki;
	
	SAutor(): imie(""),nazwisko(""),typ(' '),liczba(0),ksiazki(nullptr) {}
	
	~SAutor(){
		if(ksiazki){
			delete[] ksiazki;
			ksiazki = nullptr;
			}
		}
		
	bool wczytaj(ifstream&);
	bool wypisz(ostream& out = cout);
	};


struct SLista{
	string nazwa;
	unsigned int liczba_autorow;
	SAutor* autor;
	
	SLista(): nazwa(""),liczba_autorow(0),autor(nullptr){}
	
	bool wczytaj(ifstream&);
	bool wypisz(ostream& out = cout);
	float srednia();
	
	~SLista(){
		if(autor){
			delete[] autor;
			autor = nullptr;
			}
		}
	};

bool SAutor::wczytaj(ifstream& input){
	if(!input.good()){
		cerr << "Blad wczytywania z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	input >> SAutor::imie;	
	if(!input.good()){
		cerr << "Blad wczytywania  imienia z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	input >> SAutor::nazwisko;	
	if(!input.good()){
		cerr << "Blad wczytywania  nazwiska z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	input >> SAutor::typ;	
	if(!input.good()){
		cerr << "Blad wczytywania  typu z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	input >> SAutor::liczba;	
	if(!input.good()){
		cerr << "Blad wczytywania  liczby z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	if(SAutor::liczba <0){
		cerr << "Liczba ostatnio wydanych ksiazek danego typu musi byc >0" << endl;
		return -1;
		}
	SAutor::ksiazki = new string[SAutor::liczba];
	for(unsigned int i=0;i<SAutor::liczba;i++){
		input >> SAutor::ksiazki[i];	
		if(!input.good()){
			cerr << "Blad wczytywania  liczby z pliku input.txt" << endl;
			input.ignore();
			input.clear();
			input.close();
			return false;
		}
		}	
			
	return true;			
	}

bool SAutor::wypisz(ostream& out){

	if(!out.good()){
		cerr << "Blad wypisywania w plik output.txt" << endl;
		out.clear();
		return false;
		}
		
	out << SAutor::imie << "\t";
	if(!out.good()){
		cerr << "Blad wypisywania imienia w plik output.txt" << endl;
		out.clear();
		return false;
		}
	out << SAutor::nazwisko << "\t";
	if(!out.good()){
		cerr << "Blad wypisywania nazwiska w plik output.txt" << endl;
		out.clear();
		return false;
		}
	out << SAutor::typ << "\t";
	if(!out.good()){
		cerr << "Blad wypisywania typu w plik output.txt" << endl;
		out.clear();
		return false;
		}		
	out << SAutor::liczba << "\t";
	if(!out.good()){
		cerr << "Blad wypisywania liczby w plik output.txt" << endl;
		out.clear();
		return false;
		}	
	
	for(unsigned int i=0;i<SAutor::liczba;i++){
		if(!(out << SAutor::ksiazki[0])){
			cerr << "Blad wypisywania " << endl;
			out.clear();
			return false;
			}
		}	
			
	return true;	
	}

bool SLista::wczytaj(ifstream& input){
	if(!input.good()){
		cerr << "Blad wczytywania z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	input >> SLista::nazwa;
	if(!input.good()){
		cerr << "Blad wczytywania nazwy z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}	
	input >> SLista::liczba_autorow;
	if(!input.good()){
		cerr << "Blad wczytywania liczby autorow z pliku input.txt" << endl;
		input.ignore();
		input.clear();
		input.close();
		return false;
		}
	if(SLista::liczba_autorow<1){
		cerr << "Liczba autorow na tej liscie musi byc >1" << endl;
		input.ignore();
		input.clear();
		input.close();
		return -1;
		}	
	
	SLista::autor = new SAutor[SLista::liczba_autorow];
	for(unsigned int i=0;i<SLista::liczba_autorow;i++){
		SLista::autor[i].wczytaj(input);
		}
		
	return true;		
	}

bool SLista::wypisz(ostream& out){
	if(!out.good()){
		cerr << "Blad wypisuwania do pliku output.txt" << endl;
		out.clear();
		return false;
		}
	out << SLista::nazwa << "\n";
	if(!out.good()){
		cerr << "Blad wypisuwania nazwy do pliku output.txt" << endl;
		out.clear();
		return false;
		}
	out << SLista::liczba_autorow << "\n";
	if(!out.good()){
		cerr << "Blad wypisuwania liczby autorow  do pliku output.txt" << endl;
		out.clear();
		return false;
		}
	
	
	for(unsigned int i=0;i<SLista::liczba_autorow;i++){
		SLista::autor[i].wypisz(out);
		}
	
	return true;
	}
	
float SLista::srednia(){
	
	float s = 0;
	
	for(unsigned int i=0;i<SLista::liczba_autorow;i++){
		if(SLista::autor[i].typ == 'B'){
			s+= SLista::autor[i].liczba;
			
			}
		}
	return s;	
	}



int main(int argc,char** argv){
	if(argc != 3){
		cerr << "Podano nie prawidlowa ilosc. Prawidlowo: <input.txt><output.txt>" << endl;
		return -1;
		}
	
	ifstream input(argv[1]);
	ofstream out(argv[2]);
	
	if(!(input.good() && out.good())){
		cerr << "Blad pracy z plikami" << endl;
		input.ignore();
		input.clear();
		input.close();
		
		
		out.clear();
		out.close();
		return -1;
		}
	
	
	SLista lista;
	if(lista.wczytaj(input)){
		if(!lista.wypisz(out)){
			cerr << "Blad wypisywania do pliku output.txt" << endl;
			input.ignore();
			input.clear();
			input.close();
			
			out.clear();
			out.close();
			return -1;
			}
		if(!lista.wypisz()){
			cerr << "Blad wypisywania do pliku output.txt" << endl;
			input.ignore();
			input.clear();
			input.close();
			
			
			out.clear();
			out.close();
			return -1;
			}	
			
		float sred = lista.srednia();
		cout << "\nSrednia wynosi: " << sred << endl;
			
			
		}else{
			cerr << "Blad wczywywania do listy" << endl;
			input.ignore();
			input.clear();
			input.close();
			
			
			out.clear();
			out.close();
			return -1;
			}
	
	
	
	
	
	
	;
	
	input.close();
	out.close();
	
	return 0;
	}
