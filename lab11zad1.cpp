#include <iostream>
#include <string>

using namespace std;

// Structure representing a car
struct sAuto {
    string nazwa;
    string model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
};

// Function to read data for a single car by reference
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
    return true;
}

// Function to read data for a single car by pointer
bool wczytaj(sAuto* Auto) {
    cout << "Podaj nazwę: ";
    cin >> Auto->nazwa;
    cout << "Podaj model: ";
    cin >> Auto->model;
    cout << "Podaj rok produkcji: ";
    cin >> Auto->rok;
    cout << "Podaj rodzaj skrzyni biegów (A | M): ";
    cin >> Auto->skrzynia;
    cout << "Podaj pojemność: ";
    cin >> Auto->pojemnosc;
    cout << "Podaj moc silnika: ";
    cin >> Auto->moc;
    return true;
}

// Function to read data for an array of cars
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

// Function to read data for an array of cars by pointer
bool wczytaj(sAuto* t, const short n) {
    for (int i = 0; i < n; ++i) {
        cout << "Wprowadź dane dla samochodu " << i + 1 << ":" << endl;
        if (!wczytaj(t[i])) {
            delete[] t;
            return false;
        }
    }
    return true;
}

// Function to read data for an array of cars by reference
bool wczytaj1(sAuto*& t, const short n) {
    for (int i = 0; i < n; ++i) {
        cout << "Wprowadź dane dla samochodu " << i + 1 << ":" << endl;
        if (!wczytaj(&t[i])) {
            delete[] t;
            return false;
        }
    }
    return true;
}

// Function to display a single car
void wypisz(const sAuto* Auto) {
    cout << Auto->nazwa << "\t" << Auto->model << "\t" << Auto->rok << "\t"
         << Auto->skrzynia << "\t" << Auto->pojemnosc << "\t" << Auto->moc << endl;
}

// Function to display an array of cars
void wypisz(const sAuto* t, const short n) {
    for (int i = 0; i < n; ++i) {
        wypisz(&t[i]);
    }
}

// Function to display cars meeting age criterion
void selektor(const sAuto* t, const short n, const short ile) {
    bool jest = false;
    cout << "Samochody o nie więcej niż " << ile << " lat:" << endl;
    for (int i = 0; i < n; ++i) {
        if (2024 - t[i].rok <= ile) {
            wypisz(&t[i]);
            jest = true;
        }
    }
    if (!jest) {
        cout << "Brak samochodów spełniających kryterium." << endl;
    }
}

// Function to free memory allocated for an array of cars
void usun(sAuto*& tab) {
    if (tab) {
        delete[] tab;
        tab = nullptr;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Podaj ilość aut: <ilosc>\n";
        return -1;
    }

    short rozmiar = atoi(argv[1]);
    short kryterium;

    sAuto* tab1 = wczytaj(rozmiar);
    if (tab1 == nullptr) {
        cerr << "Nie udało się wczytać danych." << endl;
        return -1;
    }
    cout << "Wprowadzone samochody:" << endl;
    wypisz(tab1, rozmiar);
    cout << "Podaj ile lat maksymalnie mogą mieć samochody: ";
    cin >> kryterium;
    selektor(tab1, rozmiar, kryterium);

    sAuto* tab2 = new sAuto[rozmiar];
    if (!wczytaj(tab2, rozmiar)) {
        cerr << "Nie udało się wczytać danych." << endl;
        return -1;
    }
    cout << "Wprowadzone samochody:" << endl;
    wypisz(tab2, rozmiar);
    cout << "Podaj ile lat maksymalnie mogą mieć samochody: ";
    cin >> kryterium;
    selektor(tab2, rozmiar, kryterium);

    sAuto* tab3 = new sAuto[rozmiar];
    if (!wczytaj1(tab3, rozmiar)) {
        cerr << "Nie udało się wczytać danych." << endl;
        return -1;
    }
    cout << "Wprowadzone samochody:" << endl;
    wypisz(tab3, rozmiar);
    cout << "Podaj ile lat maksymalnie mogą mieć samochody: ";
    cin >> kryterium;
    selektor(tab3, rozmiar, kryterium);

    usun(tab1);
    usun(tab2);
    usun(tab3);

    return 0;
}


    usun(tablica);

    return 0;
}
