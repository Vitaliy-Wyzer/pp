#include <iostream>
#include <string>
#include <fstream>

struct SAuto {
    std::string marka;
    std::string model;
    int liczba_drzwi;
    std::string kolor;
    int moc;
    double pojemnosc_silnika;

    SAuto() : marka(""), model(""), liczba_drzwi(0), kolor(""), moc(0), pojemnosc_silnika(0.0) {}

    SAuto(std::string marka, std::string model, int liczba_drzwi, std::string kolor, int moc, double pojemnosc_silnika)
        : marka(marka), model(model), liczba_drzwi(liczba_drzwi), kolor(kolor), moc(moc), pojemnosc_silnika(pojemnosc_silnika) {} 
};


void inicjuj(SAuto& samochod, std::string marka, std::string model, int liczba_drzwi, std::string kolor, int moc, double pojemnosc_silnika) {
    samochod.marka = marka;
    samochod.model = model;
    samochod.liczba_drzwi = liczba_drzwi;
    samochod.kolor = kolor;
    samochod.moc = moc;
    samochod.pojemnosc_silnika = pojemnosc_silnika;
}

void inicjuj(SAuto* samochod, std::string marka, std::string model, int liczba_drzwi, std::string kolor, int moc, double pojemnosc_silnika) {
    samochod->marka = marka;
    samochod->model = model;
    samochod->liczba_drzwi = liczba_drzwi;
    samochod->kolor = kolor;
    samochod->moc = moc;
    samochod->pojemnosc_silnika = pojemnosc_silnika;
}

void pobierz(SAuto& samochod) {
    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    std::cout << "Marka:\n";
    std::cin >> marka;
    std::cout << "Model:\n";
    std::cin >> model;
    std::cout << "Liczba drzwi:\n";
    std::cin >> liczba_drzwi;
    std::cout << "Kolor:\n";
    std::cin >> kolor;
    std::cout << "Moc:\n";
    std::cin >> moc;
    std::cout << "Pojemnosc silnika:\n";
    std::cin >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);
}

void pobierz(SAuto* samochod) {
    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    std::cout << "Marka:\n";
    std::cin >> marka;
    std::cout << "Model:\n";
    std::cin >> model;
    std::cout << "Liczba drzwi:\n";
    std::cin >> liczba_drzwi;
    std::cout << "Kolor:\n";
    std::cin >> kolor;
    std::cout << "Moc:\n";
    std::cin >> moc;
    std::cout << "Pojemnosc silnika:\n";
    std::cin >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);
}


void info(SAuto& samochod) {
    std::cout << "Marka: " <<  samochod.marka << std::endl;
    std::cout << "Model: " <<  samochod.model << std::endl;
    std::cout << "Liczba drzwi: " <<  samochod.liczba_drzwi << std::endl;
    std::cout << "Kolor: " <<  samochod.kolor << std::endl;
    std::cout << "Moc: " <<  samochod.moc << std::endl;
    std::cout << "pojemnosc silnika: " <<  samochod.pojemnosc_silnika << "\n\n";
}

void info(SAuto* samochod) {
    std::cout << "Marka: " <<  samochod->marka << std::endl;
    std::cout << "Model: " <<  samochod->model << std::endl;
    std::cout << "Liczba drzwi: " <<  samochod->liczba_drzwi << std::endl;
    std::cout << "Kolor: " <<  samochod->kolor << std::endl;
    std::cout << "Moc: " <<  samochod->moc << std::endl;
    std::cout << "pojemnosc silnika: " <<  samochod->pojemnosc_silnika << "\n\n";
}

void pobierz(SAuto& samochod, std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);

    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << std::endl;
    }

    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    plik >> marka >> model >> liczba_drzwi >> kolor >> moc >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);

    plik.close();
}

void pobierz(SAuto* samochod, std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);

    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << std::endl;
    }

    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    plik >> marka >> model >> liczba_drzwi >> kolor >> moc >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);

    plik.close();
}

void pobierz(SAuto& samochod, std::ifstream& plik, std::string& nazwa_pliku) {
    plik.open(nazwa_pliku);

    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << std::endl;
    }

    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    plik >> marka >> model >> liczba_drzwi >> kolor >> moc >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);

    plik.close();
}

void pobierz(SAuto* samochod, std::ifstream& plik, std::string& nazwa_pliku) {
    plik.open(nazwa_pliku);

    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << std::endl;
    }

    std::string marka, model, kolor;
    int liczba_drzwi, moc;
    double pojemnosc_silnika;

    plik >> marka >> model >> liczba_drzwi >> kolor >> moc >> pojemnosc_silnika;

    inicjuj(samochod, marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);

    plik.close();
}


int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Uzycie: " << argv[0] << " <nazwa_pliku>\n";
        return 1;
    }

    SAuto samochod1;
    SAuto* samochod2 = new SAuto;
    SAuto samochod3;
    SAuto* samochod4 = new SAuto;
    SAuto samochod5;
    SAuto* samochod6 = new SAuto;

    std::string nazwa_pliku = argv[1];
    std::ifstream plik1;
    std::ifstream plik2;

    pobierz(samochod1);
    pobierz(samochod2);
    pobierz(samochod3, nazwa_pliku);
    pobierz(samochod4, nazwa_pliku);
    pobierz(samochod5, plik1, nazwa_pliku);
    pobierz(samochod6, plik2, nazwa_pliku);

    std::cout << "\nSamochod1:\n";
    info(samochod1);
    std::cout << "\nSamochod2:\n";
    info(samochod2);
    std::cout << "\nSamochod3:\n";
    info(samochod3);
    std::cout << "\nSamochod4:\n";
    info(samochod4);
    std::cout << "\nSamochod5:\n";
    info(samochod5);
    std::cout << "\nSamochod6:\n";
    info(samochod6);

    delete samochod2;
    delete samochod4;
    delete samochod6;

    return 0;
}   