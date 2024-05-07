#include <iostream>
#include <fstream>

using namespace std;

struct sAuto {
    string nazwa;
    string model;
    int rok_produkcji;
    char rodzaj_skrzyni;
    float pojemnosc;
    int moc_silnika;
};

void inicjuj(sAuto& auto1, ifstream& fin) {
    if (!fin.good()) {
        cerr << "Blad otwarcia pliku...\n";

        fin.clear();
        fin.close();
    }
    
    fin >> auto1.nazwa;
    fin >> auto1.model;
    fin >> auto1.rok_produkcji;
    fin >> auto1.rodzaj_skrzyni;
    fin >> auto1.pojemnosc;
    fin >> auto1.moc_silnika;

    fin.clear();
    fin.close();
}

void zapisz(sAuto& auto1, ofstream& fout) {
    if (!fout.good()) {
        cerr << "Blad otwarcia pliku...\n";

        fout.clear();
        fout.close();
    }

    fout << auto1.nazwa << "\t";
    fout << auto1.model << "\t";
    fout << auto1.rok_produkcji << "\t";
    fout << auto1.rodzaj_skrzyni << "\t";
    fout << auto1.pojemnosc << "\t";
    fout << auto1.moc_silnika << "\n";

    fout.clear();
    fout.close();
}

void wyswietl(const sAuto& autox) {
    cout << autox.nazwa << "\t" << autox.model << "\t" << autox.rok_produkcji << "\t" << autox.rodzaj_skrzyni << "\t" << autox.pojemnosc << "\t" << autox.moc_silnika << endl;
}

int main(int argc, char** argv) {
    if (argc!=3) {
        cerr << "Prosze podac argumenty: <in.txt> <out.txt>\n";
        return -1;
    }

    sAuto auto1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    inicjuj(auto1, fin);
    zapisz(auto1, fout);

    return 0;
}
