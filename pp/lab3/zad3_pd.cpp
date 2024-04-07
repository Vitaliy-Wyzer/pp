#include <iostream>

// yes, i dont use namespace std.
// pd in the name of file mean - Partly done. It has no "determinant" and "inverse_matrix" funcs

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

bool wypelnij(int** &A, const int n, const int m, int** &B, const int p, const int q, const int a, const int b) {
    A = utworz(n, m);
    B = utworz(p, q);

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            A[i][j] = a + (rand() % b);
        }
    }

    for (int i = 0; i<p; i++) {
        for (int j = 0; j<q; j++) {
            B[i][j] = a + (rand() % b);
        }
    }
    return 1;
}

bool suma(int** A, const int m, const int n, int** B, const int p, const int q, int** &C) {
    if (n == p && m == q) {
        C = utworz(n, m);
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        return 1;
    } else {
        return 0;
    }
    
}

bool roznica(int** A, const int m, const int n, int** B, const int p, const int q, int** &C) {
    if (n == p && m == q) {
        C = utworz(n, m);
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        return 1;
    } else {
        return 0;
    }
    
}

bool iloczyn(int** A, const int m, const int n, int** B, const int p, const int q, int** &C) {
    if (n == q) {
        C = utworz(n, q);
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                int sum = 0;
                for (int k = 0; k<p; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

void transponowanie(int** A, const int m, const int n, int** &C) {
    C = utworz(n, m);
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            C[i][j] = A[j][i];
        }
    }
}



int main() {

    int n, m, p, q, a, b;

    do {
        std::cout << "Wpisz ilosc wierszow A:\n";
        std::cin >> n;
        std::cout << "Wpisz ilosc kolumn A:\n";
        std::cin >> m;
    } while (n<1 || m<1);

    do {
        std::cout << "Wpisz ilosc wierszow B:\n";
        std::cin >> p;
        std::cout << "Wpisz ilosc kolumn B:\n";
        std::cin >> q;
    } while (p<1 || q<1);

    do {
        std::cout << "Wpisz minimalne znaczenie dla losowania liczb:\n";
        std::cin >> a;
        std::cout << "Wpisz maksymalne znaczenie dla losowania liczb:\n";
        std::cin >> b;
    } while (a>=b);

    int** A = nullptr, ** B = nullptr, ** C = nullptr;
    if(wypelnij(A, n, m, B, p, q, a, b)) {
        std::cout << "\nMacierz A:\n";
        wypisz(A, n, m);
        std::cout << "Macierz B:\n";
        wypisz(B, p, q);
    
        if(!suma(A, m, n, B, p, q, C)){
            std::cerr << "Macierze maja nieprawidlowe wymiary - brak sumy" << std::endl;
        }
        else{
            std::cout << "suma macierzy" << std::endl;
            wypisz(C, n, m);
        }

        if(!roznica(A, m, n, B, p, q, C)){
            std::cerr << "Macierze maja nieprawidlowe wymiary - brak roznicy" << std::endl;
        } else{
            std::cout << "roznica macierzy" << std::endl;
            wypisz(C, n, m);
        }

        
        if(!iloczyn(A, m, n, B, p, q, C)){
            std::cerr << "Macierze maja nieprawidlowe wymiary - brak iloczynu" << std::endl;
        }
        else{
            std::cout << "iloczyn macierzy" << std::endl;
            wypisz(C, n, q);
        }
        std::cout << "Macierz przed transponowaniem:" << std::endl;
        wypisz(A, n, m);
        transponowanie(A, n, m, C);
        std::cout << "Macierz po transponowaniu:" << std::endl;
        wypisz(C, m, n);
    
    } else{
        std::cerr << "Nieprawidlowe rozmiary macierzy" << std::endl;
        std::cerr << "n, m, p, q - rozmiar musi byc wiekszy od 0" << std::endl;
        std::cerr << "Uruchom program jeszcze raz i podaj prawidlowe wartosci" << std::endl;
    }

    usun(A, n);
    usun(B, p);
    usun(C, n);
}
