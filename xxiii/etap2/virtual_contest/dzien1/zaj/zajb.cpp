// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((2^n + 2^m) * (n+m)log(n))
// Złożoność pamięciowa: O(2^n * n)
// Punkty: ??? (brut)

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);

    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    set<vector<int>> slowa;
    for (int mask_a = 0; mask_a < (1 << n); mask_a++) {
        vector<int> slowo;
        for (int i = 0; i < n; i++) {
            if (mask_a >> i & 1) slowo.push_back(a[i]);
        }

        if (slowo.size() % 2 != 0) continue;
        bool bad = false;
        for (int i = 0; i + 1 < slowo.size(); i += 2) {
            if (slowo[i] != slowo[i + 1]) {
                bad = true;
                break;
            }
        }
        if (!bad) slowa.insert(slowo);
    }

    int ans = 0;
    for (int mask_a = 0; mask_a < (1 << m); mask_a++) {
        vector<int> slowo;
        for (int i = 0; i < m; i++) {
            if (mask_a >> i & 1) slowo.push_back(b[i]);
        }

        if (slowa.count(slowo)) ans = max(ans, (int)slowo.size());
    }

    cout << ans << "\n";
}