// Rozwiązanie zadania 'Suma kwadratów cyfr' z II etapu I OI.
// Autor: Paweł Putra
// Złożoność czasowa: t * O(1).
// Złożoność pamięciowa: O(1)

// Niech S_i będzie sumą kwadratów cyfr liczby n po i ruchach.
// S_1 <= 9^2 * (log_10(n) + 1),
// Skoro n <= 10^66, to S_1 <= 81 * 67 < 10^4 = O(1).
//
// Z tego dostajemy, że na pewno po conajwyżej 10^4 iteracji któraś z liczb się powtórzy.

#include <iostream>
#include <string>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        cout << s;
        if (s == "1" || s == "4") {
            cout << "\n";
            continue;
        }

        int n = 0;
        for (auto c : s) {
            int cyfra = c - '0';
            n += cyfra * cyfra;
        }

        while (n != 1 && n != 4) {
            cout << " " << n;
            int nowe_n = 0;
            while (n > 0) {
                int cyfra = n % 10;
                nowe_n += cyfra * cyfra;
                n /= 10;
            }
            n = nowe_n;
        }

        cout << " " << n << "\n";
    }
}

