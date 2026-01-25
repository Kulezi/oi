// Rozwiązanie zadania 'Zawody sportowe' z II etapu XXIV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define dbg(x) #x << " = " << x << " "
#define cerr if(false)cerr
using namespace std;
using pii = pair<int,int>;
constexpr int MAXN = 1'000'005, MOD = 1'000'000'007;

vector<pair<int,int>> g[2 * MAXN];
int vis[2 * MAXN], matched[2 * MAXN], deg[2 * MAXN], wynik[MAXN];

int edges;
void add_edge(int a, int b) {
    g[a].emplace_back(b, ++edges);
    g[b].emplace_back(a, edges);
    deg[a]++;
    deg[b]++;
}

void dfs(int v) {
    matched[v] = true;
    for (auto [u, e] : g[v]) {
        if (!vis[e]) {
            vis[e] = true;
            dfs(u);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        char typ;
        cin >> typ;

        if (typ == 'T') {
            int a;
            cin >> a;
            add_edge(i, a + n);
        } else {
            int a, b;
            cin >> a >> b;
            add_edge(i, a + n);
            add_edge(i, b + n);
        }
    }

    queue<int> q;
    for (int i = 1; i <= 2 * n; i++) {
        if (deg[i] == 1) q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        cerr << dbg(v) << endl;
        q.pop();
    
        for (auto [u, e] : g[v]) {
            if (vis[e]) continue;
            if (!matched[u] && !matched[v]) {
                int zawodnik = min(u, v);
                int miejsce = max(u, v) - n;
                cerr << dbg(zawodnik) << " " << dbg(miejsce) << endl;
                wynik[zawodnik] = miejsce;
                matched[u] = matched[v] = true;
            }

            vis[e] = true;
            deg[u]--;
            deg[v]--;
            if (deg[u] == 1) q.push(u);
        }
    }
    
    bool jednoznacznie = true;
    int sposoby = 1;
    for (int i = 1; i <= 2 * n; i++) {
        if (!matched[i]) {
            jednoznacznie = false;
            // Jedyny przypadek, w którym wychodzi nam sprzeczność to gdy ktoś niezmatchowany zostaje bez krawędzi.
            if (deg[i] == 0) sposoby = 0;
            sposoby = 2 * sposoby % MOD;
            dfs(i);
        }
    }

    if (jednoznacznie) {
        cout << "TAK\n";
        for (int i = 1; i <= n; i++) cout << wynik[i] << "\n";
    } else {
        cout << "NIE\n";
        cout << sposoby << "\n";
    }
}
