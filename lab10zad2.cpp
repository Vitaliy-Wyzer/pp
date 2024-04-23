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

void inicjuj(sAuto& auto1, const string nazwa, const string model, const int rok, const char skrzynia, const float pojemnosc, const int moc) {
    auto1.nazwa = nazwa;
    auto1.nazwa = nazwa;
    auto1.model = model;
    auto1.rok_produkcji = rok;
    auto1.rodzaj_skrzyni = skrzynia;
    auto1.pojemnosc = pojemnosc;
    auto1.moc_silnika = moc;
}

void wyswietl(const sAuto& autox) {
    cout << autox.nazwa << "\t" << autox.model << "\t" << autox.rok_produkcji << "\t" << autox.rodzaj_skrzyni << "\t" << autox.pojemnosc << "\t" << autox.moc_silnika << endl;
}

int main(int argc, char** argv) {
    if (argc != 7) {
        cerr << "\nProsze podac argumenty: <nazwa> <model> <rok produkcji> <rodzaj skrzyni> <pojemnosc silnika> <moc silnika>\n\n";
        // valgrind --leak-check=full ./test Honda Civic 2024 A 4.0 160
        return -1;
    }

    sAuto auto1;
    inicjuj(auto1, argv[1], argv[2], atoi(argv[3]), argv[4][0], atof(argv[5]), atoi(argv[6]));
    wyswietl(auto1);
    
    
    return 0;
}