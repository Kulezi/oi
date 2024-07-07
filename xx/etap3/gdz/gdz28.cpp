// Rozwiązanie do zadania 'Gdzie jest jedynka?' z III etapu XX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(1)
// Punkty: 28 (upsolve)

#include <iostream>

#include "cgdzlib.h"

int32_t main() {
    int n = inicjuj();
    // Jest tylko jedna para o różnicy n-1, 1 i n, znajdujemy ją przeglądając wszystkie pary,
    // i sprawdzamy który z jej elementów jest mniejszy, to musi być jedynka.
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (f(i, j, n - 1)) {
                if (g(i, j))
                    odpowiedz(j);
                else
                    odpowiedz(i);
            }
        }
    }
    odpowiedz(1);
}