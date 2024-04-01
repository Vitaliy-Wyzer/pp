#include <iostream>

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

SAuto inicjuj(std::string marka, std::string model, int liczba_drzwi, std::string kolor, int moc, double pojemnosc_silnika) {
    return SAuto(marka, model, liczba_drzwi, kolor, moc, pojemnosc_silnika);
}

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


int main() {
    SAuto samochod1 = inicjuj("Toyota", "Corolla", 4, "Czerwony", 150, 2.0);

    SAuto samochod2;
    inicjuj(samochod2, "Ford", "Focus", 5, "Niebieski", 120, 1.6);

    SAuto* samochod3 = new SAuto();
    inicjuj(samochod3, "BMW", "X5", 5, "Czarny", 300, 3.0);

    std::cout << "Samochod1:\n";
    std::cout << "Nazwa: " << samochod1.marka << " " << samochod1.model << std::endl;
    std::cout << "Cechy: drzwi - " << samochod1.liczba_drzwi << ", moc - " << samochod1.moc << ", pojemnosc silnika - " << samochod1.pojemnosc_silnika << "\n";
    std::cout << std::endl;

    std::cout << "Samochod2:\n";
    std::cout << "Nazwa: " << samochod2.marka << " " << samochod2.model << std::endl;
    std::cout << "Cechy: drzwi - " << samochod2.liczba_drzwi << ", moc - " << samochod2.moc << ", pojemnosc silnika - " << samochod2.pojemnosc_silnika << "\n";
    std::cout << std::endl;

    std::cout << "Samochod3:\n";
    std::cout << "Nazwa: " << samochod3->marka << " " << samochod3->model << std::endl;
    std::cout << "Cechy: drzwi - " << samochod3->liczba_drzwi << ", moc - " << samochod3->moc << ", pojemnosc silnika - " << samochod3->pojemnosc_silnika << "\n";
    std::cout << std::endl;

    delete samochod3;

    return 0;
}