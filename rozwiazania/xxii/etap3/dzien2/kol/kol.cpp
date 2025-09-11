// Rozwiązanie do zadania 'Kolekcjoner Bajtemonów' z III etapu XXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(2 * 10^9))
// Złożoność pamięciowa: O(log(2 * 10^9))
// Punkty: 100 (upsolve)

#include <vector>
#include "ckollib.h"
using namespace std;
constexpr int MAX_BIT = 30;
int main() {
    int pierwsza = 0, ile_pierwsza = 0;
    int druga = 0, ile_druga = 0;

    vector<int> ile_bitu(MAX_BIT+1, 0);
    for (int x = karta(); x != 0; x = karta()) {
        if (pierwsza == 0) {
            pierwsza = x;
        } else if (x != pierwsza && druga == 0) {
            druga = x;
        }

        if (x == pierwsza) ile_pierwsza++;
        if (x == druga) ile_druga++;

        for (int i = 0; i <= MAX_BIT; i++)
            if (x >> i & 1) ile_bitu[i]++;
    }

    int kopii_niekradzionych = max(ile_pierwsza, ile_druga);
    int skradziona = 0;
    for (int i = 0; i <= MAX_BIT; i++) {
        if (ile_bitu[i] % kopii_niekradzionych) skradziona += 1 << i;
    }

    if (druga == 0) skradziona = pierwsza;
    odpowiedz(skradziona);
}