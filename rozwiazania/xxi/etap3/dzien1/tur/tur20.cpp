// Rozwiązanie brutalne do zadania 'Turystyka' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n * n^2)
// Złożoność pamięciowa: O(n + m)
// Punkty: 20 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 20005;
vector<int> g[MAXN];
int c[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> c[i];

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = INT_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> dominated(n, false);
        int sum = 0;
        for (int v = 0; v < n; v++) {
            if (mask >> v & 1) {
                dominated[v] = true;
                for (auto u : g[v]) dominated[u] = true;
                sum += c[v];
            }
        }

        if(find(dominated.begin(), dominated.end(), false) == dominated.end()) {
            ans = min(ans, sum);
        }
    }

    cout << ans << "\n";
}