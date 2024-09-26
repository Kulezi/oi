// Rozwiązanie do zadania 'Izolator' z IX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100'005;
int t[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    long long A = 0;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        A += t[i];
    }

    sort(t+1, t + n + 1);

    // Mając jakieś ustawienie warstw przesunięcie z tych pomiędzy minimum i maksimum
    // nie pogorszy wyniku => opłaca się brać na zmianę minimalne i maksymalne wartości.
    for (int i = 1; n - i + 1 > i; i++) {
        A += t[n-i+1] - t[i];
    }

    cout << A << "\n";
}