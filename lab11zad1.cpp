#include <iostream>
#include <string>

using namespace std;

// Struktura reprezentująca samochód
struct sAuto {
    string nazwa;
    string model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
};

// Funkcja do wczytywania danych pojedynczego samochodu
bool wczytaj(sAuto& Auto) {
    cout << "Podaj nazwę: ";
    cin >> Auto.nazwa;
    cout << "Podaj model: ";
    cin >> Auto.model;
    cout << "Podaj rok produkcji: ";
    cin >> Auto.rok;
    cout << "Podaj rodzaj skrzyni biegów (A | M): ";
    cin >> Auto.skrzynia;
    cout << "Podaj pojemność: ";
    cin >> Auto.pojemnosc;
    cout << "Podaj moc silnika: ";
    cin >> Auto.moc;
    return 1;
}

// Funkcja do wczytywania tablicy samochodów
sAuto* wczytaj(const short n) {
    sAuto* t = new sAuto[n];
    for (int i = 0; i < n; ++i) {
        cout << "Wprowadź dane dla samochodu " << i + 1 << ":" << endl;
        if (!wczytaj(t[i])) {
            delete[] t;
            return nullptr;
        }
    }
    return t;
}

// Funkcja do wyświetlania pojedynczego samochodu
void wypisz(const sAuto* Auto) {
    cout << Auto->nazwa << "\t" << Auto->model << "\t" << Auto->rok << "\t"
         << Auto->skrzynia << "\t" << Auto->pojemnosc << "\t" << Auto->moc << endl;
}

// Funkcja do wyświetlania tablicy samochodów
void wypisz(const sAuto* t, const short n) {
    for (int i = 0; i < n; ++i) {
        wypisz(&t[i]);
    }
}

// Funkcja do wyświetlania samochodów spełniających kryterium wieku
void selektor(const sAuto* t, const short n, const short ile) {
    bool jest = 0;
    cout << "Samochody o nie więcej niż " << ile << " lat:" << endl;
    for (int i = 0; i < n; ++i) {
        if (2024 - t[i].rok <= ile) {
            wypisz(&t[i]);
            jest = 1;
        }
    }
    if (!jest) {
        cout << "Brak samochodów spełniających kryterium." << endl;
    }
}

void usun(sAuto*& tab) {
    if (tab) {
        delete[] tab;
        tab = nullptr;
    }
}

int main(int argc, char** argv) {
    if (argc!=2) {
        cerr << "Podaj ilość aut: <ilosc>\n";
        return -1;
    }


    short rozmiar = atoi(argv[1]);

    sAuto* tablica = wczytaj(rozmiar);
    if (tablica == nullptr) {
        cerr << "Błąd podczas wczytywania danych." << endl;
        return -1;
    }

    cout << "Wprowadzone samochody:" << endl;
    wypisz(tablica, rozmiar);

    short kryterium;
    cout << "Podaj ile lat maksymalnie mogą mieć samochody: ";
    cin >> kryterium;

    selektor(tablica, rozmiar, kryterium);

    usun(tablica);

    return 0;
}
