#include <iostream>
#include <string>

using namespace std;

struct sAuto{
	string nazwa;
	string model;
	int rok;
	char skrzynia;
	float pojemnosc;
	int moc;
	
	};

sAuto inicjuj(const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc){
	sAuto samo;
	samo.nazwa = nazwa;
	samo.model = model;
	samo.rok = rok;
	samo.skrzynia = skrzynia;
	samo.pojemnosc = pojemnosc;
	samo.moc = moc;
	return samo;
	}

void inicjuj1(sAuto& samo, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc,const int moc){
	samo.nazwa = nazwa;
	samo.model = model;
	samo.rok = rok;
	samo.skrzynia = skrzynia;
	samo.pojemnosc = pojemnosc;
	samo.moc = moc;
	}

void inicjuj(sAuto* samo, const string nazwa, const string model,const int rok, const char skrzynia, const float pojemnosc, const int moc){
	samo->nazwa = nazwa;
	samo->model = model;
	samo->rok = rok;
	samo->skrzynia = skrzynia;
	samo->pojemnosc = pojemnosc;
	samo->moc = moc;
	}

sAuto wczytaj(sAuto (*wfun)(const string, const string, const int, const char, const float, const int)){
	sAuto samo;
	
	cout << "Podaj nazwe samochodu: ";
	cin >> samo.nazwa;
	cout << "Podaj model samochodu: ";
	cin >> samo.model;
	cout << "Podaj rok samochodu: ";
	cin >> samo.rok;
	cout << "Podaj rodzaj skrzyni biegow(M/A): ";
	cin >> samo.skrzynia;
	cout << "Podaj pojemnosc silnika samochodu: ";
	cin >> samo.pojemnosc;
	cout << "Podaj moc silnika samochodu: ";
	cin >> samo.moc;
	
	return wfun(samo.nazwa,samo.model,samo.rok,samo.skrzynia,samo.pojemnosc,samo.moc);
	}

void wczytaj1(sAuto& samo, void (*wfun)(sAuto&, const string,const string, const int, const char, const float, const int)){
	
	
	cout << "Podaj nazwe samochodu: ";
	cin >> samo.nazwa;
	cout << "Podaj model samochodu: ";
	cin >> samo.model;
	cout << "Podaj rok samochodu: ";
	cin >> samo.rok;
	cout << "Podaj rodzaj skrzyni biegow(M/A): ";
	cin >> samo.skrzynia;
	cout << "Podaj pojemnosc silnika samochodu: ";
	cin >> samo.pojemnosc;
	cout << "Podaj moc silnika samochodu: ";
	cin >> samo.moc;
	
	wfun(samo,samo.nazwa,samo.model,samo.rok,samo.skrzynia,samo.pojemnosc,samo.moc);
	}

void wczytaj(sAuto* samo, void (*wfun)(sAuto*, const string,const string, const int, const char, const float, const int)){
	
	
	cout << "Podaj nazwe samochodu: ";
	cin >> samo->nazwa;
	cout << "Podaj model samochodu: ";
	cin >> samo->model;
	cout << "Podaj rok samochodu: ";
	cin >> samo->rok;
	cout << "Podaj rodzaj skrzyni biegow(M/A): ";
	cin >> samo->skrzynia;
	cout << "Podaj pojemnosc silnika samochodu: ";
	cin >> samo->pojemnosc;
	cout << "Podaj moc silnika samochodu: ";
	cin >> samo->moc;
	
	wfun(samo,samo->nazwa,samo->model,samo->rok,samo->skrzynia,samo->pojemnosc,samo->moc);
	}

void wyswietl(const sAuto samo){
	cout << samo.nazwa << "\t" << samo.model << "\t" << samo.rok << "\t" << samo.skrzynia << "\t" << samo.pojemnosc << "\t" << samo.moc << "\t" << endl;
	}
	
void wyswietl1(const sAuto &samo){
	cout << samo.nazwa << "\t" << samo.model << "\t" << samo.rok << "\t" << samo.skrzynia << "\t" << samo.pojemnosc << "\t" << samo.moc << "\t" << endl;
	}

void wyswietl(const sAuto *samo){
	cout << samo->nazwa << "\t" << samo->model << "\t" << samo->rok << "\t" << samo->skrzynia << "\t" << samo->pojemnosc << "\t" << samo->moc << "\t" << endl;
	}	
	
void selector(const sAuto samo){
	if(2024 - samo.rok <= 5){
		cout  << samo.nazwa << " " << samo.model << " ma mniej niz 5 lat:" << endl;
		
		}else{
			cout << "Samochod ma wiecej niz 5 lat." << endl;
			}
	}	
	
void selector1(const sAuto& samo){
	if(2024 - samo.rok <= 5){
		cout  << samo.nazwa << " " << samo.model << " ma mniej niz 5 lat:" << endl;
		}else{
			cout << "Samochod ma wiecej niz 5 lat." << endl;
			}
	}
	
void selector(const sAuto* samo){
	if(2024 - samo->rok <= 5){
		cout  << samo->nazwa << " " << samo->model << " ma mniej niz 5 lat:" << endl;
		}else{
			cout << "Samochod ma wiecej niz 5 lat." << endl;
			}
	}			

int main() {
	sAuto sam1 = {"Toyota", "Corolla Cross", 2023, 'A',2.0,187};
	wyswietl(sam1);
	
	sAuto sam2 = wczytaj(inicjuj);
	cout << "***** Zwykla zmiena: *****" << endl;
	wyswietl(sam2);
	selector(sam2);
	
	cout << "******** Zmiena referencyjna ********" << endl;
	sAuto& r_sam = sam1;
	wczytaj1(r_sam,inicjuj1);
	wyswietl1(r_sam);
	selector1(r_sam);
	
	cout << "******** Zmiena wskaznikowa ********" << endl;
	sAuto* w_sam = &sam2;
	wczytaj(w_sam,inicjuj);
	wyswietl(w_sam);
	selector(w_sam);
  
  
  return 0;
}
