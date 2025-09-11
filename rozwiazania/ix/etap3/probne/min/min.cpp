// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n).
// Punkty: 100 (upsolve), zajęło 15 minut od przeczytania do wbicia na szkopule.

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005;

char znak[MAXN];
string ans;
void nawiasuj(int l, int r, char szukany) {
    while (l <= r && znak[l] != szukany) {
        ans += "-";
        l++;
    }

    if (l <= r && znak[l] == szukany) {
        ans += "(";

        int ostatni = r;

        // Tu juz sie zatrzyma w najgorszym przypadku dla ostatni=l.
        while (znak[ostatni] != szukany) ostatni--;
        nawiasuj(l, ostatni, (szukany == '+' ? '-' : '+'));
        // znajdz od prawej.
        ans += ")";
        for (int i = ostatni + 1; i <= r; i++) ans += "-";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> znak[i];
    }

    nawiasuj(1, n - 1, '+');
    cout << ans << "\n";
    return 0;
}
