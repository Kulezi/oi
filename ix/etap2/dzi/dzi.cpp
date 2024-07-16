// Rozwiązanie do zadania 'Działka' z II etapu IX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<int> ban(n + 1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // Trzyma pary (indeks, ban).
        vector<pair<int, int>> poczatki;
        auto dodaj = [&](int j, int r, int b) {
            while (!poczatki.empty() && poczatki.back().second < b) {
                j = poczatki.back().first;
                ans = max((i - poczatki.back().second) * (r - j), ans);
                
                poczatki.pop_back();
            }
            
            if (poczatki.empty() || poczatki.back().second != b) poczatki.emplace_back(j, b);
        };

        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if (x == 1) ban[j] = i;
            dodaj(j, j, ban[j]);
        }

        dodaj(n + 1, n + 1, 0);
    }

    cout << ans << "\n";
}