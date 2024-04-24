#include <iostream>
#include <string>

using namespace std;

struct sAuto {
    string nazwa, model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
};

sAuto inicjuj(const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    sAuto sam;

    sam.nazwa = nazwa;
    sam.model = model;
    sam.rok = rok;
    sam.skrzynia = skrzynia;
    sam.pojemnosc = pojemnosc;
    sam.moc = moc;

    return sam;
}

void inicjuj1(sAuto& Auto, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    Auto.nazwa = nazwa;
    Auto.model = model;
    Auto.rok = rok;
    Auto.skrzynia = skrzynia;
    Auto.pojemnosc = pojemnosc;
    Auto.moc = moc;
}

void inicjuj(sAuto* Auto, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    Auto->nazwa = nazwa;
    Auto->model = model;
    Auto->rok = rok;
    Auto->skrzynia = skrzynia;
    Auto->pojemnosc = pojemnosc;
    Auto->moc = moc;
}

sAuto wczytaj(sAuto (*wfun)(const string, const string, const int, const char, const float, const int)) {
    sAuto sam;
    
    cout << "\nPodaj nazwe: ";
    cin >> sam.nazwa;
    cout << "\nPodaj model: ";
    cin >> sam.model;
    cout << "\nPodaj rok: ";
    cin >> sam.rok;
    cout << "\nPodaj skrzynie (A/M): ";
    cin >> sam.skrzynia;
    cout << "\nPodaj pojemnosc: ";
    cin >> sam.pojemnosc;
    cout << "\nPodaj moc: ";
    cin >> sam.moc;

    return wfun(sam.nazwa, sam.model, sam.rok, sam.skrzynia, sam.pojemnosc, sam.moc);
}

void wczytaj1(sAuto& Auto, void (*wfun)(sAuto&, const string, const string, const int, const char, const float, const int)) {
    cout << "\nPodaj nazwe: ";
    cin >> Auto.nazwa;
    cout << "\nPodaj model: ";
    cin >> Auto.model;
    cout << "\nPodaj rok: ";
    cin >> Auto.rok;
    cout << "\nPodaj skrzynie (A/M): ";
    cin >> Auto.skrzynia;
    cout << "\nPodaj pojemnosc: ";
    cin >> Auto.pojemnosc;
    cout << "\nPodaj moc: ";
    cin >> Auto.moc;
}

void wczytaj(sAuto* Auto, void (*wfun)(sAuto*, const string, const string, const int, const char, const float, const int)) {
    cout << "\nPodaj nazwe: ";
    cin >> Auto->nazwa;
    cout << "\nPodaj model: ";
    cin >> Auto->model;
    cout << "\nPodaj rok: ";
    cin >> Auto->rok;
    cout << "\nPodaj skrzynie (A/M): ";
    cin >> Auto->skrzynia;
    cout << "\nPodaj pojemnosc: ";
    cin >> Auto->pojemnosc;
    cout << "\nPodaj moc: ";
    cin >> Auto->moc;
}

void wyswietl(sAuto Auto) {
    cout << Auto.nazwa << "\t" << Auto.model << "\t" << Auto.rok << "\t" << Auto.skrzynia << "\t" << Auto.pojemnosc << "\t" << Auto.moc << "\n";
}

void wyswietl1(sAuto& Auto) {
    cout << Auto.nazwa << "\t" << Auto.model << "\t" << Auto.rok << "\t" << Auto.skrzynia << "\t" << Auto.pojemnosc << "\t" << Auto.moc << "\n";
}

void wyswietl(sAuto* Auto) {
    cout << Auto->nazwa << "\t" << Auto->model << "\t" << Auto->rok << "\t" << Auto->skrzynia << "\t" << Auto->pojemnosc << "\t" << Auto->moc << "\n";
}

void selektor(sAuto Auto) {
    if (Auto.rok < 2019) {
        cout << "Samochod ma wiecej niz 5 lat!\n";
    } else {
        cout << "Samochod ma nie wiecej niz 5 lat!\n";
    }
}

void selektor1(sAuto& Auto) {
    if (Auto.rok < 2019) {
        cout << "Samochod ma wiecej niz 5 lat!\n";
    } else {
        cout << "Samochod ma nie wiecej niz 5 lat!\n";
    }
}

void selektor(sAuto* Auto) {
    if (Auto->rok < 2019) {
        cout << "Samochod ma wiecej niz 5 lat!\n";
    } else {
        cout << "Samochod ma  nie wiecej niz 5 lat!\n";
    }
}

int main() {
    
    sAuto sam1 = {"Hyundai", "Elantra", 2021, 'A', 2.6, 190};
    wyswietl(sam1);

    cout << "\n***** Zwykla zmienna *****\n";
    sAuto sam2 = wczytaj(inicjuj);
    wyswietl(sam2);
    selektor(sam2);

    cout << "\n***** Zmienna referencyjna *****\n";
    sAuto& r_sam = sam1;
    wczytaj1(r_sam, inicjuj1);
    wyswietl1(r_sam);
    selektor(r_sam);

    cout << "\n***** Zmienna wskaznikowa *****\n";
    sAuto* w_sam = &sam2;
    wczytaj(w_sam, inicjuj);
    wyswietl(w_sam);
    selektor(w_sam);

    return 0;
}

