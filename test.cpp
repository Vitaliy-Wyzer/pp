#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

void utworz(float*& t, const int n) {
    t = new float[n];
    for (int i = 0; i<n; i++) {
        t[i] = 0;
    }
}

void wypelnij(float*&t, const int n, const int a, const int b) {
    for (int i = 0; i<n; i++) {
        t[i] = a + static_cast<float>(rand()) / RAND_MAX * b-a;
    }
}

void wypisz(float*t, const int n) {
    for (int i = 0; i<n; i++) {
        std::cout << t[i] << "\t";
    }
    std::cout << std::endl;
}

int mail(std::string str) {
    size_t pos = str.find('@');
    if (pos != std::string::npos) {
        return static_cast<int>(pos);
    }
    return -1;
}

bool selektor(std::string nazwa_out, std::string nazwa_in) {
    std::ifstream in(nazwa_in);
    std::ofstream out(nazwa_out, std::ios::app);
    if (in.good() && out.good()) {
        std::string tekst = "";
        while (!in.eof()) {
            in >> tekst;
            if (mail(tekst) != -1) {
                out << tekst << std::endl;
            }
        } 

        in.clear();
        in.ignore();
        in.close();

        out.clear();
        out.close();

        return 1;
    }

    std::cerr << "Blad otwarcia plikow\n";

    in.clear();
    in.ignore();
    in.close();

    out.clear();
    out.close();

    return 0;


}

int main(int argc, char** argv) {
    if (argc!=5) {
        std::cerr << "No nieee, poprosze 4 argumenty: <min> <max> <out.txt> <in.txt>\n";
        return -1;
    }

    float min, max;
    min = atof(argv[1]);
    max = atof(argv[2]);

    if (min >= 0 || max <0 ) {
        std::cerr << "trzeba ujemny min i dodatni max\n";
        return -1;
    }

    int n;
    do {
        std::cout << "Prosze podac rozmiar tablicy:\n";
        std::cin >> n;
    } while (n<1);

    float* t = nullptr;
    utworz(t, n);
    wypelnij(t, n, min, max);
    wypisz(t, n);

    const std::string file_out = argv[3];
    const std::string file_in = argv[4];
    if (selektor(file_out, file_in)) {
        std::cout << "Dane zostaly zapisane w pliku " << file_out << std::endl;
    } else {
        std::cout << "Blad przy zapisie w plik...\n";
    }

    delete[] t;

    return 0;
}
