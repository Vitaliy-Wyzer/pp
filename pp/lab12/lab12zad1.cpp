#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SProstopadloscian {
    float dlugosc;
    float szerokosc;
    float wysokosc;
};

SProstopadloscian* wczytaj(const char* plik_wej, int& n) {
    ifstream plik(plik_wej);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku." << endl;
        // thx
        plik.ignore();
        plik.close();
        // thx
        return nullptr;
    }
    plik >> n;
    SProstopadloscian* prostopadl = new SProstopadloscian[n];
    for (int i = 0; i < n; ++i) {
		if(!(plik >> prostopadl[i].dlugosc)){
		cerr << "Nie udalo sie wczytac dlugosc!" << endl;
            // thx
			plik.clear();
			plik.close();
			if(prostopadl != nullptr){
				delete[] prostopadl;
				prostopadl = nullptr;
				return prostopadl;
			}
            // thx
		}
        // thx
		if(!(plik >> prostopadl[i].szerokosc)){
		cerr << "Nie udalo sie wczytac szerokosc!" << endl;
			plik.clear();
			plik.close();
			if(prostopadl != nullptr){
				delete[] prostopadl;
				prostopadl = nullptr;
				return prostopadl;
			}
        // thx
		}
        // thx
		if(!(plik >> prostopadl[i].wysokosc)){
		cerr << "Nie udalo sie wczytac wysokosc!" << endl;
			plik.clear();
			plik.close();
			if(prostopadl != nullptr){
				delete[] prostopadl;
				prostopadl = nullptr;
				return prostopadl;
			}
		}
        // thx
	}
    // thx
	plik.clear();
    // thx
	plik.close();
	return prostopadl;
}

float pole(const SProstopadloscian& p) {
    return 2 * (p.dlugosc * p.szerokosc + p.dlugosc * p.wysokosc + p.szerokosc * p.wysokosc);
}

int znajdz_pole(const SProstopadloscian* p, const int n) {
    int indeks = 0;
    // camel case?
    float maxPole = pole(p[0]);
    for (int i = 1; i < n; ++i) {
        float aktPole = pole(p[i]);
        if (aktPole > maxPole) {
            maxPole = aktPole;
            indeks = i;
        }
    }
    return indeks;
}

float objetosc(const SProstopadloscian& p) {
    return p.dlugosc * p.szerokosc * p.wysokosc;
}

float znajdz_objetosc(const SProstopadloscian* p, const int n) {
    // camel case?
    float maxObj = objetosc(p[0]);
    for (int i = 1; i < n; ++i) {
        float aktObj = objetosc(p[i]);
        if (aktObj > maxObj) {
            maxObj = aktObj;
        }
    }
    return maxObj;
}

bool wysokosc(const SProstopadloscian& p1, const SProstopadloscian& p2) {
    return p1.wysokosc > p2.wysokosc;
}

void sortuj(SProstopadloscian* p, const int n, bool (*wfun)(const SProstopadloscian&, const SProstopadloscian&)) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (wfun(p[j], p[j + 1])) {
                SProstopadloscian temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void wypisz(const SProstopadloscian* p) {
    for (int i = 0; i < 5; ++i) {
        cout << "Dlugosc " << p[i].dlugosc << "\tSzerokosc " << p[i].szerokosc << "\tWysokosc " << p[i].wysokosc << endl;
    }
}

void wypisz(const SProstopadloscian* p, const int n) {
    for (int i = 0; i < n; ++i) {
        cout <<  "Dlugosc " << p[i].dlugosc << "\tSzerokosc " << p[i].szerokosc << "\tWysokosc " << p[i].wysokosc << endl;
    }
}

bool wypisz(const SProstopadloscian& p, ofstream& fout) {
    // wow
	if(!(fout << p.dlugosc)){
		cerr << "Nie udalo sie wczytac dlugosc!" << endl;
		fout.clear();
		fout.close();
	}
	if(!(fout << p.szerokosc)){
		cerr << "Nie udalo sie wczytac szerokosc!" << endl;
		fout.clear();
		fout.close();
	}
	if(!(fout << p.wysokosc)){
		cerr << "Nie udalo sie wczytac wysokosc!" << endl;
		fout.clear();
		fout.close();
	}
	else
		fout << p.dlugosc << "\t" << p.szerokosc << "\t" << p.wysokosc << endl;
    // wow
    return 1;
}

bool wypisz(const SProstopadloscian* p, const int n, const string& plik_wyj) {
    ofstream fout(plik_wyj);
    if (!fout.is_open()) {
        cerr << "Nie mozna otworzyc pliku." << endl;
        // thx
        fout.clear();
        fout.close();
        // thx
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (!wypisz(p[i], fout)) {
			cerr << "Blad podczas zapisu danych" << endl;
            // thx
			fout.clear();
			fout.close();
            // thx
            return false;
        }
    }
    fout << "\n";
    // clear? ;(
    fout.close();
    return true;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Podaj: " << argv[0] << " <plik_wejsciowy> <plik_wyjsciowy>" << endl;
        return 1;
    }
    int n = 0;
    SProstopadloscian* p = wczytaj(argv[1], n);
    if (p) {
        wypisz(p);
        if (wypisz(p, n, argv[2])) {
            cout << "Zapisano pomyslnie do pliku." << endl;
        } else {
            cerr << "Cos poszlo nie tak!" << endl;
        }
        cout << "Prostopadloscian o najwiekszym polu powierzchni znajduje sie na pozycji: " << znajdz_pole(p, n) << endl;
        cout << "Najwieksza objetosc prostopadloscianu wynosi: " << znajdz_objetosc(p, n) << endl;
        sortuj(p, n, wysokosc);
        cout << "Posortowane wzgledem wysokosci prostopadlosciany:" << endl;
        wypisz(p, n);
        if (wypisz(p, n, argv[2])) {
            cout << "Zapisano pomyslnie do pliku." << endl;
        } else {
            cerr << "Cos poszlo nie tak!" << endl;
        }
        if(p != nullptr){
			delete[] p;
			p = nullptr;
		}
    } else {
        cerr << "Blad podczas wczytywania danych." << endl;
    }
    return 0;
}
