// Rozwiązanie zadania 'Strajki' z II etapu XXIV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n + m * log(n)).
// Złożoność pamięciowa: O(n).

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 1'000'000'005;
int n, m;
int vis[MAXN], strajk[MAXN], t[MAXN], L[MAXN], R[MAXN], par[MAXN];
vector<int> g[MAXN];

struct Fenwick {
    int n;
    vector<int> fw;

    Fenwick(int n) : n(n), fw(n, 0) {}

    void add(int x, int delta) {
        for (;x < n; x |= x + 1)
            fw[x] += delta;
    }
    int sum(int r) {
        int res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += fw[r];
        return res;
    }
    int sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l-1);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        assert(a < b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    int T = 0;

    // Ukorzeniamy drzewo w jedynce i numerujemy je w kolejności przechodzenia bfsem,
    // dzięki temu synowie wierzchołka zajmują spójny przedział numerów.
    queue<int> q;
    q.push(1);
    t[1] = ++T;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        L[v] = INF, R[v] = -INF;
        for (auto u : g[v]) {
            if (!t[u]) {
                t[u] = ++T;
                par[u] = v;
                L[v] = min(L[v], t[u]);
                R[v] = max(R[v], t[u]);
                q.push(u);
            }
        }
    }


    int spojne = 1;
    Fenwick fw(n+2);
    cin >> m;
    while (m--) {
        int v;
        cin >> v;
        if (v > 0) {
            assert(!strajk[v]);
        } else {
            v = -v;
            assert(strajk[v]);
        }
        
        strajk[v] = 1 - strajk[v];
        int ile = (R[v] >= L[v] ? (R[v] - L[v] + 1) - fw.sum(L[v], R[v]) : 0);
        if (par[v] && !strajk[par[v]]) ile++;

        if (strajk[v]) {
            spojne += ile - 1;
            fw.add(t[v], 1);
        } else {
            spojne -= ile - 1;
            fw.add(t[v], -1);
        }

        cout << spojne << "\n";
    }
}
