// Rozwiązanie do zadania 'Gdzie jest jedynka?' z III etapu XX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(1)
// Punkty: 100 (upsolve)

#include <iostream>

#include "cgdzlib.h"
using namespace std;

int n;

int odlegly_o_d(int pos, int d) {
    for (int i = 1; i <= n; i++) {
        if (i == pos) continue;
        if (f(pos, i, d)) return i;
    }

    return 0;
}

int najdalszy(int pos, int d_min, int d_max) {
    while (d_min < d_max) {
        int d = (d_min + d_max + 1) / 2;
        if (odlegly_o_d(pos, d))
            d_min = d;
        else
            d_max = d - 1;
    }

    return odlegly_o_d(pos, d_min);
}

int32_t main() {
    n = inicjuj();
    if (n == 1) {
        odpowiedz(1);
        return 0;
    }

    // Najdalszy element pod względem różnicy wartości to zawsze 1 albo n.
    // Znajdujemy dwa elementy, dla których najdalsze elementy się różnią.
    int pol = (n + 1) / 2;
    int a = 1, b = odlegly_o_d(a, pol);
    while (b == 0) {
        a++, b = odlegly_o_d(a, pol);
    }

    // Znajdujemy oba końce wyszukiwaniem binarnym.
    int kandydat_a = najdalszy(a, pol, n - 1);
    int kandydat_b = najdalszy(b, pol, n - 1);

    // I sprawdzamy, który to jedynka.
    if (g(kandydat_a, kandydat_b))
        odpowiedz(kandydat_b);
    else
        odpowiedz(kandydat_a);
}
