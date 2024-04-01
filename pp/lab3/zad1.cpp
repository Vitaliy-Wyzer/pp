#include <iostream>

// yes, i dont use namespace std.

int** utworz(const int n, const int m) {
    // tworzenie dynamicznej 2d tablicy
    int** arr = new int*[n];

    // iteracja po elementach tablicy
    for (int i = 0; i<n; i++) {
        // tworzenie dynamicznych podtablic
        arr[i] = new int[m];

        // iteracja po elementach podtablicy
        for (int j = 0; j<m; j++) {
            // wyzerowanie elementow tablicy
            arr[i][j] = 0;
        }
    }
    return arr;
}

void utworz(int**& t, const int n, const int m) {
    // alokacja pamieci dla 2d tablicy
    t = new int*[n];

    // iteracja po elementach tablicy
    for (int i = 0; i<n; i++) {
        // tworzenie dynamicznych podtablic
        t[i] = new int[m];

        // iteracja po elementach podtablicy
        for (int j = 0; j<m; j++) {
            // wyzerowanie tablicy
            t[i][j] = 0;
        }
    }
}


void utworz1(int** t, const int n, const int m) {
    // iteracja po elementach tablicy
    for (int i = 0; i<n; i++) {
        // iteracja po elementach podtablicy
        for (int j = 0; j<m; j++) {
            // wyzerowanie elemeto tablicy
            t[i][j] = 0;
        }
    }

}


void usun(int**& dest, const int n) {
    // iteracja po elementach tablicy (podtablicach)
    for (int i = 0; i<n; i++) {
        // usuniecie podtablic
        delete[] dest[i];
    }

    // usuniecie tablicy
    delete[] dest;
}

void wypisz(int** t, const int n, const int m) {
    // iteracja po elementach tablicy
    for (int i = 0; i<n; i++) {
        // iteracja po elementach podtablicy
        for (int j = 0; j<m; j++) {
            // wypisanie elementow przez spacje
            std::cout << t[i][j] << " ";
        }
        // pusta linija miedzy wierszami
        std::cout << std::endl;
    }
    // pusta linija dla czytelnosci
    std::cout << std::endl;
}

void wypelnij(int** &t, const int n, const int m) {
    // komunikat do uzytkownika
    std::cout << "Wpisz liczby do mecierzy:\n";
    // iteracja po elementach tablicy
    for (int i=0; i<n; i++) {
        // iteracja po elementah podtablicy
        for (int j=0; j<m; j++) {
            // wpisanie elementow przez uzytkownika
            std::cin >> t[i][j];
        }
    }
    // pusta linija po wpisaniu 
    std::cout << std::endl;
}


void wypelnij(int** &t, const int n, const int m, const int a, const int b) {
    // iteracja po elementach tablicy
    for (int i = 0; i<n; i++) {
        // iteracja po elementach podtablicy
        for (int j = 0; j<m; j++) {
            // wypelnia tablice elementami losowymi w zakresie [a, b]
            t[i][j] = a + (rand() % b);
        }
    }
}


int main() {
    
    int n;
    int m;
    int a;
    int b;

    // debug: n and m must be more or equel to 1
    do {
        std::cout << "Wpisz ilosc wierszow:\n";
        std::cin >> n;
        std::cout << "Wpisz ilosc kolumn:\n";
        std::cin >> m;
    } while (n<1 || m<1);

    // debug: a must be less than b
    do {
        std::cout << "Wpisz minimalne znaczenie dla losowania liczb:\n";
        std::cin >> a;
        std::cout << "Wpisz maksymalne znaczenie dla losowania liczb:\n";
        std::cin >> b;
    } while (a>=b);
    


    int** tab = utworz(n, m);
    int** tab2 = nullptr;
    int** tab3 = new int*[n];
    for (int i = 0; i<n; i++) {
        tab3[i] = new int[m];
    }

    utworz(tab2, n, m);
    utworz1(tab3, n, m);

    wypelnij(tab, n, m);
    wypelnij(tab2, n, m, a, b);

    std::cout << "Tablica wypelniona liczbami podanymi przez uztkownika:\n";
    wypisz(tab, n, m);
    std::cout << "Tablica wypelnina liczbami losowanymi z zarkesu [" << a << ", " << b << "]\n";
    wypisz(tab2, n, m);
    std::cout << "Tablica wyzerowana:\n";
    wypisz(tab3, n, m);

    usun(tab, n);
    usun(tab2, n);
    usun(tab3, n);

    return 0;
}