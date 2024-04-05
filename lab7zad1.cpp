#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void wypisz_tablice_2d(unsigned int** tab_2d, unsigned int wiersze, unsigned int kolumny) {
    for (unsigned int i = 0; i < wiersze; ++i) {
        for (unsigned int j = 0; j < kolumny; ++j) {
            cout << "[" << tab_2d[i][j] << "]";
        }
        cout << endl;
    }
}

unsigned int ile_wystapien_znaku(const string& zrodlo, char znak) {
    unsigned int count = 0;
    for (char c : zrodlo) {
        if (c == znak) count++;
    }
    return count;
}

unsigned int znak_na_numer(char znak) {
    if (znak >= 'a' && znak <= 'z') {
        return znak - 'a';
    } else {
        return 111; // jeżeli znak nie należy do alfabetu angielskiego
    }
}

void statystyka(unsigned int tablica[], const char* napis) {
    for (unsigned int i = 0; i < 26; ++i) {
        tablica[i] = 0; // zero out the array
    }

    for (const char* ptr = napis; *ptr; ++ptr) {
        unsigned int index = znak_na_numer(*ptr);
        if (index != 111) {
            tablica[index]++;
        }
    }
}

unsigned int** statystyki(const string* napisy, unsigned int rozmiar) {
    unsigned int** wynik = new unsigned int*[rozmiar];
    for (unsigned int i = 0; i < rozmiar; ++i) {
        wynik[i] = new unsigned int[26];
        statystyka(wynik[i], napisy[i].c_str());
    }
    return wynik;
}

int main(int argc, char** argv) {
    if (argc!=5) {
        cerr << "Podano malo argumentow: <napis1> <napis2> <napis3> <znak>";
        // ./name "ala ma" "kota" "abcdefghijklmnopqrstuvwxyz" 'd'
        return -1;
    }
    unsigned n = 3;
    string napisy[n] = {argv[1], argv[2], argv[3]};
    unsigned int** statsy = statystyki(napisy, n);
    wypisz_tablice_2d(statsy, n, 26);

    // Zwolnienie pamięci
    for (unsigned int i = 0; i < 3; ++i) {
        delete[] statsy[i];
    }
    delete[] statsy;

    // додаткове завдання з лабки: вивести індекс символу
    char znak = argv[4][0]; // argv[4] -> char array (tablica znaków), argv[4][0] -> char
    cout << "\nZnak '" << znak << "' ma indeks: " << znak_na_numer(znak) << endl;


    return 0;
}
