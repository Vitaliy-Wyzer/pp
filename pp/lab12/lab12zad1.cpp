#include <iostream>
#include <cmath>

using namespace std;

struct SPunkt {
    double x, y;
};

struct SProsta {
    double a, b; // Współczynniki równania y = ax + b
};

struct SOkrag {
    double a, b, r; // Środek (a,b) i promień r
};

struct SRownanie {
    double a, b, c; // Współczynniki równania kwadratowego ax^2 + bx + c
};

int rozw_rown(const SRownanie& r, SPunkt& p1, SPunkt& p2) {
    double delta = r.b * r.b - 4 * r.a * r.c;
    cout << delta << "\n";
    if (delta > 0) {
        p1.x = (-r.b + sqrt(delta)) / (2 * r.a);
        cout << p1.x << "\n";
        p2.x = (-r.b - sqrt(delta)) / (2 * r.a);
        p1.y = p2.y = 0;
        return 2; // Dwa miejsca zerowe
    } else if (delta == 0) {
        p1.x = p2.x = -r.b / (2 * r.a);
        p1.y = p2.y = 0;
        return 1; // Jedno miejsce zerowe
    } else {
        return 0; // Brak miejsc zerowych
    }
}

int pkt_przec(const SProsta& p, const SOkrag& o, SPunkt& p1, SPunkt& p2) {
    SRownanie r;
    r.a = 1 + p.a * p.a;
    r.b = 2 * p.a * (p.b - o.b) - 2 * o.a;
    r.c = o.b * o.b - o.r * o.r + o.a * o.a - 2 * p.b * o.b + p.b * p.b;

    int result = rozw_rown(r, p1, p2);
    return result;
}

bool czy_prostopadle(const SProsta& p1, const SProsta& p2) {
    return p1.a * p2.a == -1; // Sprawdzamy, czy iloczyn wspolczynnikow kierunkowych równa się -1
}

int main() {
    SPunkt p1 = {0, 0}, p2 = {0, 0};
    SProsta prosta1 = {-1.0, 3.0};
    SProsta prosta2 = {1.0, -3.0};
    SOkrag okrag = {0.0, 1.0, 2.0};
    
    int pier1 = pkt_przec(prosta1, okrag, p1, p2);
    if (pier1 == 2) {
        cout << "Prosta przecina okrag w punktach:" << endl;
        cout << "(" << p1.x << ", " << p1.y << ")" << endl;
        cout << "(" << p2.x << ", " << p2.y << ")" << endl;
    } else if (pier1 == 1) {
        cout << "Prosta jest styczna do okregu w punkcie:" << endl;
        cout << "(" << p1.x << ", " << p1.y << ")" << endl;
    } else if (pier1 == 0) {
        cout << "Prosta nie przecina okregu" << endl;
    } else {
        cout << "Brak rozwiązania - to nie jest rownanie kwadratowe" << endl;
    }
    
    cout << "Czy proste sa prostopadle? " << boolalpha << czy_prostopadle(prosta1, prosta2) << endl;

    return 0;
}
