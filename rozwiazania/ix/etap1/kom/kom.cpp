// Rozwiązanie do zadania 'Komiwojażer bajtazar' z I etapu IX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n + m) * log(n))
// Złożoność pamięciowa: O(n * log(n))
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 30'005, LOG = 16;
vector<int> g[MAXN];
int p[MAXN][LOG];
int in[MAXN], out[MAXN], dis[MAXN];
int T;
void dfs(int v) {
    in[v] = ++T;
    for (auto u : g[v]) {
        if (!in[u]) {
            p[u][0] = v;
            dis[u] = dis[v] + 1;
            dfs(u);
        }
    }
    out[v] = T;
}

bool przodek(int a, int b) { return in[a] <= in[b] && out[a] >= out[b]; }

int lca(int a, int b) {
    if (przodek(a, b)) return a;
    if (przodek(b, a)) return b;
    for (int h = LOG - 1; h >= 0; h--)
        if (!przodek(p[a][h], b)) a = p[a][h];
    return p[a][0];
}

int d(int a, int b) {
    int l = lca(a, b);
    return dis[a] + dis[b] - 2 * dis[l];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    p[1][0] = 1;

    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);
    for (int h = 1; h < LOG; h++)
        for (int v = 1; v <= n; v++) p[v][h] = p[p[v][h - 1]][h - 1];

    int m;
    cin >> m;

    int skad = 1, wynik = 0;
    while (m--) {
        int dokad;
        cin >> dokad;
        wynik += d(skad, dokad);
        skad = dokad;
    }

    cout << wynik << "\n";
}