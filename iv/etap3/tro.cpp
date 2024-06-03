// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n).
// Punkty: 100 (upsolve).

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    int m;
    cin >> m;

    vector<int> szare(n+1, 0);
    while(m--) {
        int x, y;
        cin >> x >> y;
        szare[x]++;
        szare[y]++;
    }

    long long roznobarwne = 0;
    for (int i = 1; i <= n; i++) {
        int czarne = n - 1 - szare[i];

        roznobarwne += czarne * szare[i];
    }

    roznobarwne /= 2;

    long long wszystkie = 1LL * n * (n-1) * (n-2) / 6;
    cout << wszystkie - roznobarwne << "\n";
}