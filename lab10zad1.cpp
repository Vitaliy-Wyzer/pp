#include <iostream>

using namespace std;

struct sAuto {
    string nazwa;
    string model;
    int rok_produkcji;
    char rodzaj_skrzyni;
    float pojemnosc;
    int moc_silnika;
};

sAuto inicjuj(const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    return {nazwa, model, rok, skrzynia, pojemnosc, moc};
}

void inicjuj(sAuto& auto1, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    auto1.nazwa = nazwa;
    auto1.nazwa = nazwa;
    auto1.model = model;
    auto1.rok_produkcji = rok;
    auto1.rodzaj_skrzyni = skrzynia;
    auto1.pojemnosc = pojemnosc;
    auto1.moc_silnika = moc;
}

void inicjuj1(sAuto* auto2, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    auto2->nazwa = nazwa;
    auto2->model = model;
    auto2->rok_produkcji = rok;
    auto2->rodzaj_skrzyni = skrzynia;
    auto2->pojemnosc = pojemnosc;
    auto2->moc_silnika = moc;
}

sAuto wczytaj(sAuto (*wfun)(const string, const string, const int, const char, const float, const int)) {
    string nazwa, model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
    
    cout << "Podaj nazwe: ";
    cin >> nazwa;
    cout << "Podaj model: ";
    cin >> model;
    cout << "Podaj rok produkcji: ";
    cin >> rok;
    cout << "Podaj rodzaj skrzyni biegow (A/M): ";
    cin >> skrzynia;
    cout << "Podaj pojemnosc silnika: ";
    cin >> pojemnosc;
    cout << "Podaj moc silnika: ";
    cin >> moc;
    
    return wfun(nazwa, model, rok, skrzynia, pojemnosc, moc);
}

void wczytaj(sAuto& auto3, void (*wfun)(sAuto&, const string, const string, const int, const char, const float, const int)) {
    string nazwa, model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
    
    cout << "Podaj nazwe: ";
    cin >> nazwa;
    cout << "Podaj model: ";
    cin >> model;
    cout << "Podaj rok produkcji: ";
    cin >> rok;
    cout << "Podaj rodzaj skrzyni biegow: ";
    cin >> skrzynia;
    cout << "Podaj pojemnosc silnika: ";
    cin >> pojemnosc;
    cout << "Podaj moc silnika: ";
    cin >> moc;
    
    wfun(auto3, nazwa, model, rok, skrzynia, pojemnosc, moc);
}

void wczytaj1(sAuto* auto4, void (*wfun)(sAuto*, const string, const string, const int, const char, const float, const int)) {
    string nazwa, model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
    
    cout << "Podaj nazwe : ";
    cin >> nazwa;
    cout << "Podaj model: ";
    cin >> model;
    cout << "Podaj rok produkcji: ";
    cin >> rok;
    cout << "Podaj rodzaj skrzyni biegow (A/M): ";
    cin >> skrzynia;
    cout << "Podaj pojemnosc silnika: ";
    cin >> pojemnosc;
    cout << "Podaj moc silnika: ";
    cin >> moc;
    
    wfun(auto4, nazwa, model, rok, skrzynia, pojemnosc, moc);
}

void wyswietl(const sAuto& autox) {
    cout << autox.nazwa << "\t" << autox.model << "\t" << autox.rok_produkcji << "\t" << autox.rodzaj_skrzyni << "\t" << autox.pojemnosc << "\t" << autox.moc_silnika << endl;
}

void selektor(const sAuto& autox) {
    if (autox.rok_produkcji > 2020) {
        wyswietl(autox);
    }
}

int main() {
    
    sAuto auto1 = wczytaj(inicjuj);
    
    sAuto auto2;
    wczytaj(auto2, inicjuj);
    
    sAuto* auto3 = new sAuto();
    wczytaj1(auto3, inicjuj1);
    
    cout << "Samochody: " << endl;
    wyswietl(auto1);
    wyswietl(auto2);
    wyswietl(*auto3);
    cout << endl;
    
    cout << "Samochody, ktore maja mniej niz 5 lat: " << endl;
    selektor(auto1);
    selektor(auto2);
    selektor(*auto3);
    
    if (auto3) 
        delete auto3;
    
    return 0;
}
