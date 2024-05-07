#include <iostream>

struct sAuto {
    std::string nazwa, model;
    int rok;
    char skrzynia;
    float pojemnosc;
    int moc;
};

bool wczytaj(sAuto& Auto) {
    std::cout << "Podaj nazwe: ";
    if (!(std::cin >> Auto.nazwa)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    std::cout << "Podaj model: ";
    if (!(std::cin >> Auto.model)) {
        std::cerr << "\nBlad podania modelu\n";
        return 0;
    }
    std::cout << "Podaj rok: ";
    if (!(std::cin >> Auto.rok)) {
        std::cerr << "\nBlad podania roku\n";
        return 0;
    }
    std::cout << "Podaj typ skrzyni (A/M): ";
    if (!(std::cin >> Auto.skrzynia)) {
        std::cerr << "\nBlad podania typu skrzyni\n";
        return 0;
    }
    std::cout << "Podaj pojemnosc silnika: ";
    if (!(std::cin >> Auto.pojemnosc)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    std::cout << "Podaj moc silnika: ";
    if (!(std::cin >> Auto.moc)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    return 1;
}

bool wczytaj(sAuto* Auto) {
    std::cout << "Podaj nazwe: ";
    if (!(std::cin >> Auto->nazwa)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    std::cout << "Podaj model: ";
    if (!(std::cin >> Auto->model)) {
        std::cerr << "\nBlad podania modelu\n";
        return 0;
    }
    std::cout << "Podaj rok: ";
    if (!(std::cin >> Auto->rok)) {
        std::cerr << "\nBlad podania roku\n";
        return 0;
    }
    std::cout << "Podaj typ skrzyni (A/M): ";
    if (!(std::cin >> Auto->skrzynia)) {
        std::cerr << "\nBlad podania typu skrzyni\n";
        return 0;
    }
    std::cout << "Podaj pojemnosc silnika: ";
    if (!(std::cin >> Auto->pojemnosc)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    std::cout << "Podaj moc silnika: ";
    if (!(std::cin >> Auto->moc)) {
        std::cerr << "\nBlad podania nazwy\n";
        return 0;
    }
    return 1;
}

sAuto* wczytaj(const short n) {
    sAuto* Auto = new sAuto [n];
    for (int i=0; i<n; i++) {
        wczytaj(Auto[i]);
    }
    return Auto;
}

bool wczytaj(sAuto* t, const short n) {
    if (t == 0) {
        return 0;
    }

    for (int i=0; i<n; i++) {
        wczytaj(&t[i]);
    }
    return 1;
}

bool wczytaj1(sAuto*& t, const short n) {
    if (t == 0) {
        return 0;
    }

    for (int i=0; i<n; i++) {
        wczytaj(t[i]);
    }
    return 1;
}

bool wypisz(const sAuto* Auto) {
    if (Auto) {
        std::cout << Auto->nazwa << "\t" << Auto->model << "\t" << Auto->rok << "\t"
              << Auto->skrzynia << "\t" << Auto->pojemnosc << "\t" << Auto->moc << "\n";
    return 1;
    }
    return 0;
}

bool wypisz(const sAuto* t, const short n) {
    if (t) {
        for (int i=0; i<n; i++) {
            wypisz(&t[i]);
        }
        return 1;
    }
    return 0;
}

void selektor(const sAuto* t, const short n, const short ile) {
    bool found = false;
    std::cout << "Samochody o nie wiecej niz " << ile << " lat:\n";
    for (int i=0; i<n; i++) {
        if (2024-ile <= t[i].rok) {
            wypisz(&t[i]);
            found = true;
        }
    }
    if (!found) {
        std::cout << "Nie ma samochodow o zadanym kryterium.\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "\nProsze podac: <liczba samochodow>\n";
        return -1;
    }

    const short n = atoi(argv[1]);
    short lat;

    sAuto * t1 = wczytaj(n);
    if (t1) {
        if(wypisz(t1, n));
            std::cout << "\nPodaj kryterium (liczbe lat):";
            if (!(std::cin >> lat)) {
                std::cerr << "Blad podania kryterium\n";
                return -1;
            }
            std::cout << std::endl;
            selektor(t1, n, lat);
        
    }
    sAuto * t2 = new sAuto [n];
    if (wczytaj(t2, n)) {
        if (wypisz(t2, n)) {
            std::cout << "\nPodaj kryterium (liczbe lat):";
            if (!(std::cin >> lat)) {
                std::cerr << "Blad podania kryterium\n";
                return -1;
            }
            std::cout << std::endl;
            selektor(t2, n, lat);
        }
    }
    sAuto *t3 = new sAuto [n];
    if (wczytaj1(t3, n)) {
        if (wypisz(t3, n)) {
            std::cout << "\nPodaj kryterium (liczbe lat):";
            if (!(std::cin >> lat)) {
                std::cerr << "Blad podania kryterium\n";
                return -1;
            }
            std::cout << std::endl;
            selektor(t3, n, lat);
        }
    }

    delete [] t1;
    delete [] t2;
    delete [] t3;

    return 0;
}
