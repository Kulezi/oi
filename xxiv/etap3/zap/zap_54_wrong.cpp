// Rozwiązanie błędne do zadania 'Zapiekanki' z III etapu XXIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 56 (upsolve, na zawodach chyba by weszło na 92)

#include <iostream>
#define int long long
using namespace std;
using ll = long long;
constexpr int MAXN = 3005;
int t[MAXN];
ll dp[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int k, z, d;
    cin >> k >> z >> d;

    for (int i = 1; i <= k; i++) {
        cin >> t[i];
    }

    int koniec = d;
    int pieczone = 0;
    int suma = 0;
    for (int i = 1; i <= k; i++) {
        // W obecnym pieczeniu moze wejsc jak:
        // Piekarnik nie jest jeszcze pelny
        // i klient przychodzi przed końcem pieczenia.
        // wpp. pieczenie robimy jak najwcześniej.
        if (pieczone < z && t[i] <= koniec) {
            pieczone++;
        } else {
            pieczone = 1;
            koniec = max(t[i], koniec + d);
        }

        suma += koniec - t[i];
    }

    cout << suma << "\n";
}