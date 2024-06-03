// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: chyba O(n*W), nie pamiętam treści teraz.
// Punkty: 20

#include <bits/stdc++.h>
#define int long long
using namespace std;
int t[1 << 20], dest[1 << 20], sum[1 << 20], res, n, a, b, s1, s2;
vector<int> g[1 << 20];
main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i], s1 += t[i];
    for (int i = 1; i <= n; i++) cin >> dest[i], s2 += dest[i];
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    if (s1 != s2) {
        cout << "NIE";
        return 0;
    }
    set<int> s;
    for (int i = 1; i <= n; i++) {
        if (t[i] - dest[i] > 0) s.insert(i);
        t[i] -= dest[i];
    }
    while (!s.empty()) {
        int v = *s.begin();
        int hits = t[v] / (int)g[v].size();
        if (hits * g[v].size() < t[v]) hits++;
        res += hits;
        for (auto u : g[v]) {
            t[v] -= hits;
            t[u] += hits;
            if (t[u] > 0) s.insert(u);
        }
        s.erase(v);
    }
    cout << "TAK\n";
    cout << res;
}