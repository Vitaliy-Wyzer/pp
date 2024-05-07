#include <iostream>
#include <fstream>

using namespace std;

bool czytaj(ifstream& fin, double**& A, unsigned int& m, unsigned int& n, double**& B, unsigned int& p, unsigned int& q) {
    if (!fin.is_open()) {
        cerr << "Blad otwarcia pliku wejsciowego." << endl;
        return false;
    }

    fin >> m >> n;

    A = new double*[m];
    for (unsigned int i = 0; i < m; ++i) {
        A[i] = new double[n];
        for (unsigned int j = 0; j < n; ++j) {
            fin >> A[i][j];
        }
    }

    fin >> p >> q;

    B = new double*[p];
    for (unsigned int i = 0; i < p; ++i) {
        B[i] = new double[q];
        for (unsigned int j = 0; j < q; ++j) {
            fin >> B[i][j];
        }
    }

    return true;
}

void utworz(double**& matrix, unsigned int rows, unsigned int cols) {
    matrix = new double*[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
        for (unsigned int j = 0; j < cols; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void zapisz(ofstream& fout, double** matrix, unsigned int rows, unsigned int cols) {
    if (!fout.is_open()) {
        cerr << "Blad zapisu do pliku wyjsciowego." << endl;
        return;
    }

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            fout << matrix[i][j] << " ";
        }
        fout << endl;
    }
}

void usun(double**& matrix, unsigned int rows) {
    if (matrix) {
        for (unsigned int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

bool suma(double** A, unsigned int m, unsigned int n, double** B, unsigned int p, unsigned int q, double**& C) {
    if (m != p || n != q) {
        return false;
    }

    utworz(C, m, n);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return true;
}

bool roznica(double** A, unsigned int m, unsigned int n, double** B, unsigned int p, unsigned int q, double**& C) {
    if (m != p || n != q) {
        return false;
    }

    utworz(C, m, n);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return true;
}

bool iloczyn(double** A, unsigned int m, unsigned int n, double** B, unsigned int p, unsigned int q, double**& C) {
    if (n != p) {
        return false;
    }

    utworz(C, m, q);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < q; ++j) {
            C[i][j] = 0;
            for (unsigned int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return true;
}

void transponowanie(double** A, unsigned int m, unsigned int n, double**& C) {
    utworz(C, n, m);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            C[j][i] = A[i][j];
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    double** A = nullptr;
    double** B = nullptr;
    double** C = nullptr;
    unsigned int n, m, p, q;

    if (czytaj(fin, A, m, n, B, p, q)) {
        if (!suma(A, m, n, B, p, q, C))
            cerr << "Macierze maja nieprawidlowe wymiary" << endl;
        else {
            fout << "suma macierzy" << endl;
            zapisz(fout, C, m, n);
            usun(C, m);
        }

        if (!roznica(A, m, n, B, p, q, C))
            cerr << "Macierze maja nieprawidlowe wymiary" << endl;
        else {
            fout << "roznica macierzy" << endl;
            zapisz(fout, C, m, n);
            usun(C, m);
        }

        if (!iloczyn(A, m, n, B, p, q, C))
            cerr << "Macierze maja nieprawidlowe wymiary" << endl;
        else {
            fout << "iloczyn macierzy" << endl;
            zapisz(fout, C, m, q);
            usun(C, m);
        }

        fout << "macierz przed transponowaniem" << endl;
        zapisz(fout, B, p, q);
        fout << "macierz transponowana" << endl;
        transponowanie(B, p, q, C);
        zapisz(fout, C, q, p);
        usun(C, q);
    }

    usun(B, p);
    usun(A, m);
    
    fin.close();
    fout.close();

    return 0;
}
