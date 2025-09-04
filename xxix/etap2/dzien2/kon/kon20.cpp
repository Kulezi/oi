// Rozwiązanie brutalne do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q^2)
// Złożoność pamięciowa: O(n)
// Punkty: 20 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005;

vector<int> g[MAXN];
void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    add_edge(1, 2);
    int q;
    cin >> q;
    
    int n = 2;
    while (q--) {
        string s;
        int x;
        cin >> s >> x;

        if (s == "W") {
            add_edge(x, ++n);
        } else if (s == "Z") {
            ++n;
            for (auto v : g[x]) {
                add_edge(v, n);
            }
        } else if (s == "?") {
            cout << g[x].size() << "\n";
        }
    }
}
