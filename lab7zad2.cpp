#include <iostream>
#include <string>

using namespace std;

unsigned int potega_10(unsigned int wykladnik) {
	unsigned int wynik = 10;
	if(wykladnik>0) {
		for(unsigned int i=1; i<wykladnik; ++i) {
			wynik *= 10;
		}
	} else if(wykladnik==0) {
		wynik = 1;
	} else {
		cerr << "Wykladnik potegi powinien byc liczba calkowita nieujemna.\n";
		exit(0);
	}
	return wynik;
}

unsigned int ile_cyfr(unsigned int liczba) {
	unsigned int ile = 0;
	while(liczba>=1) {
		liczba /= 10;
		++ile;
	}
	return ile;
}

unsigned int doklej_do_liczby(unsigned int zrodlo, unsigned int cyfra, bool na_poczatek=true) {
	if(cyfra>9) {
		cerr << "Cyfra powinna byc liczba calkowita z przedzialu <0; 9>\n";
		return zrodlo;
	}
	
	if(na_poczatek) {
		unsigned int rozmiar = ile_cyfr(zrodlo);
		zrodlo = cyfra*potega_10(rozmiar) + zrodlo;
	} else {
		zrodlo = zrodlo*10 + cyfra;
	}
	return zrodlo;
}

unsigned int znak_na_cyfre(char znak) {
	if(znak>47 && znak<58) {
		return znak-48;
	} else return 0;
}

unsigned int zamien_na_liczbe(const char* zrodlo) {
	unsigned int liczba = 0;
	unsigned int rozmiar = 0;
	while(zrodlo[rozmiar]!='\0') ++rozmiar;
	for(unsigned int i=0; zrodlo[i]!='\0'; ++i) {
		if(zrodlo[i]>='0' && zrodlo[i]<='9') liczba = liczba + znak_na_cyfre(zrodlo[i])*potega_10(rozmiar-i-1);
		else cerr << "\nUwaga! Znak powinien byc cyfra.\n";
	}
	return liczba;
}

int main(int argc, char** argv) {
	unsigned jakas_liczba = 6572;
    cout << doklej_do_liczby(jakas_liczba,5) << endl;
    //56572
    cout << doklej_do_liczby(jakas_liczba,1,false) << endl;
    //65721
    unsigned jakas_druga_liczba = zamien_na_liczbe("1234");
    cout << jakas_druga_liczba << endl;
    //1234
    jakas_druga_liczba = zamien_na_liczbe("1ert234");
    cout << jakas_druga_liczba << endl;
    //1000234

    char* ciag = new char[100];

    if (argc!=2) {
        cout << "\nNie podano argumentow przy uruchomieniu programu, Prosze podac ciag znakow:\n";
        cin >> ciag;
    }

    if (argc==2) {
        ciag = argv[1];
    }

    cout << "\n" << zamien_na_liczbe(ciag);
    delete[] ciag;

    return 0;
}
