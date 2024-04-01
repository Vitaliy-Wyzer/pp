#include <iostream>

int* utworz(const int n) {
    int* arr = new int[n];

    for (int i = 0; i<n; i++) {
        arr[i] = 0;
    }

    return arr;
}

void wypelnij(int*& arr, const int n, const int a, const int b) {
    for (int i=0; i<n; i++) {
        arr[i] = a + (rand() % b);
    }
}

void wypisz(int* arr, const int n) {
    std::cout << "Elementy tablicy wylosowanej:\n";
    for (int i=0; i<n; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

bool kryterium(const int a, const int b) {
    return (a>b);
}

void sortuj(int*& arr, const int n) {
    for (int i = 0; i<n-1; i++) {
        for (int j = 0; j<n-i-1; j++) {
            if (kryterium(arr[j], arr[j+1])) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}


int main() {

    int n;
    int a;
    int b;

    do {
        std::cout << "Wpisz rozmiar tablicy:\n";
        std::cin >> n;

    } while (n<1);

    do {
        std::cout << "Wpisz minimalna wartosc do losowania:\n";
        std::cin >> a;
        std::cout << "Wpisz maksymalna wartosc do losowania:\n";
        std::cin >> b;
    } while (a>=b);

    int* tab = utworz(n);
    
    wypelnij(tab, n, a, b);
    wypisz(tab, n);
    sortuj(tab, n);
    wypisz(tab, n);

    delete[] tab;

    return 0;
}