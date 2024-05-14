#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct SWielomian {
    unsigned int stopien;
    float* wspolczynniki;
};

float losuj(const float min, const float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

float* wspolczynniki(SWielomian& w, const unsigned int stopien = 1, const float min = -5.5, const float max = 5.5) {
    w.stopien = stopien;
    w.wspolczynniki = new float[stopien + 1];
    for (unsigned int i = 0; i <= stopien; ++i) {
        w.wspolczynniki[i] = losuj(min, max);
    }
    return w.wspolczynniki;
}

float wartosc_wielomianu(const SWielomian& w, const float x) {
    float wynik = w.wspolczynniki[w.stopien];
    for (int i = w.stopien - 1; i >= 0; --i) {
        wynik = wynik * x + w.wspolczynniki[i];
    }
    return wynik;
}

void wypisz(const float w, const unsigned i) {
    if (i == 0) {
        cout << w;
    } else {
        cout << " + " << w << "*x^" << i;
    }
}

void wypisz(const SWielomian& w) {
    for (unsigned int i = 0; i <= w.stopien; ++i) {
        wypisz(w.wspolczynniki[i], i);
    }
    cout << endl;
}

void usun(SWielomian& w) {
    if (!(w.wspolczynniki)) {
        delete[] w.wspolczynniki;
        w.wspolczynniki = nullptr;
    }
}

int main(int argc, char* argv[]) {
    // prolly bad, her main is needed 
    // if (argc < 3) {
    //     cerr << "Prosze podac: <stopien> <x> <min> <max>\n";
    //     return -1;
    // }



    srand(static_cast<unsigned int>(time(0)));

    // same
    int stopien = 1;
    float x = 0.0f;
    SWielomian w;
    if (argc > 2) {
        stopien = atoi(argv[1]);
        x = atof(argv[2]);
    }
    // but at least it works

    float wartosc = 0;
    if (argc == 5) {
        float min = atof(argv[3]), max = atof(argv[4]);
        if(min < 0 && max > 0 && stopien > 1) {
            wspolczynniki(w, stopien, min, max);
            wartosc = wartosc_wielomianu(w, x);
            cout << "Wartosc wielomianu stopnia " << w.stopien - 1
                 << "dla x = " << x << " wynosi: " << wartosc << endl;
            wypisz(w);
        }
    }
    else {
        
        cout << "Podano zla wartosc min, max lub stopien. ";
        cout << "Wartosc wielomianu wyliczona zostaje dla argumentow domyslnych\n";
        cout << "stopien = 1, min = -5.5, max = 5.5\n";
        wspolczynniki(w);
        wartosc = wartosc_wielomianu(w, x);
        cout << "Wartosc wielomianu  stopnia " << w.stopien - 1
             << " dla x = " << x
             << " wynosi: " << wartosc << endl;
        wypisz(w);
    }

    usun(w);
    return 0;
}
