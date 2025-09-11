// Rozwiązanie do zadania 'Morskie opowieści' z II etapu XX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (n + m) + k)
// Złożoność pamięciowa: O(n + k)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 5015, INF = 2'000'000'000, MAXK = 1'000'005;
vector<int> g[2*MAXN], konce[MAXN];
int dis[2*MAXN], t[MAXK], d[MAXK];
int odp[MAXK];
void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

int par(int x) { return 2 * x; }
int npar(int x) { return 2 * x + 1; }

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    while (m--) {
        int a, b;
        cin >> a >> b;
        add_edge(par(a), npar(b));
        add_edge(npar(a), par(b));
    }

    for (int i = 1; i <= k; i++) {
        int s;
        cin >> s >> t[i] >> d[i];
        konce[s].push_back(i);
    }

    for (int s = 1; s <= n; s++) {
        for (int t = 1; t <= npar(n); t++) dis[t] = INF;
        queue<int> q;
        q.push(par(s));
        dis[par(s)] = 0;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : g[v]) {
                if (dis[u] > dis[v] + 1) {
                    dis[u] = dis[v] + 1;
                    q.push(u);
                }
            }
        }

        for (auto i : konce[s]) {
           
            // Przypadek brzegowy - wierzchołek izolowany.
            if (g[par(s)].size() == 0) {
                odp[i] = (t[i] == s && d[i] == 0);
            } else {
                int v = (d[i] % 2 ? npar(t[i]) : par(t[i]));
                odp[i] = (dis[v] <= d[i]);
            }

        }
    }

    for (int i = 1; i <= k; i++) cout << (odp[i] ? "TAK\n" : "NIE\n");
}