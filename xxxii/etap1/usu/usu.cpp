// Rozwiązanie do zadania 'Usuwanie' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(1)
// Złożoność pamięciowa: O(1)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int32_t main() {
    ios_base::sync_with_stdio(0);
    ll a, b;
    cin >> a >> b;

    // Sumują się do parzystej <=> obie są parzyste albo obie są nieparzyste.
    ll parzyste = b / 2 - (a - 1) / 2;
    ll nieparzyste = (b - a + 1) - parzyste;
    cout << (parzyste / 2 + nieparzyste / 2) * 2 << "\n";
}