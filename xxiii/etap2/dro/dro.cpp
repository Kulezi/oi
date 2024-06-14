// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'005;
int n, m;

vector<int> g[MAXN], grev[MAXN], scc_vertices[MAXN];
vector<int> ord;
int vis[MAXN], scc[MAXN], st[MAXN];

void dfs1(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) dfs1(u);
    }

    ord.push_back(v);
}

vector<int> component;
void dfs2(int v) {
    vis[v] = 2;
    component.push_back(v);
    for (auto u : grev[v]) {
        if (vis[u] != 2) dfs2(u);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        grev[b].push_back(a);
    }

    // Wyliczamy silnie spójne składowe algorytmem Kosaraju.
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }

    reverse(ord.begin(), ord.end());

    int N = 0;
    // Numerujemy silnie spójne składowe w kolejności topologicznej od 0 do N-1, 
    // i zapisujemy jakie wierzchołki do nich należą.
    for (auto i : ord) {
        if (vis[i] != 2) {
            int id = N++;
            dfs2(i);

            while (!component.empty()) {
                scc[component.back()] = id;
                scc_vertices[id].push_back(component.back());
                component.pop_back();
            }
        }
    }


    // Przy pomocy sum prefiksowych będziemy liczyć czy coś jest na jakimś przedziale [i+1, r(i)-1].
    vector<int> pref(N + 1, 0);
    auto add = [&](int l, int r) {
        pref[l]++;
        pref[r + 1]--;
    };

    // r(j) = min numer wierzchołka do którego jest krawędź z j, N+1, wpp.
    // Analogicznie r_rev(j) = max numer wierzchołka do którego jest krawędź z j w odwróconym grafie, -1 wpp.
    // Wierzchołek i nie będzie dobrym korzeniem wtw. gdy będzie jakieś i dla którego j < i < r(j),
    // bo nie możemy do niego dojść z j, bo musimy go przeskoczyć i nie możemy też dojść z niego do j,
    // bo wszystkie krawędzie są skierowane w przeciwną stronę.
    // Analogicznie dla odwróconego grafu z r_rev(j) < i < j.
    vector<int> r(N, N), r_rev(N, -1);
    for (int i = 0; i < N; i++) {
        for (auto u : scc_vertices[i]) {
            for (auto v : g[u]) {
                if (scc[u] == scc[v]) continue;
                assert(scc[v] > scc[u]);
                r[i] = min(r[i], scc[v]);
            }
        }

        int L = i + 1;
        int R = r[i] - 1;
        if (L <= R) {
            add(L, R);
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        for (auto u : scc_vertices[i]) {
            for (auto v : grev[u]) {
                if (scc[u] == scc[v]) continue;
                assert(scc[v] < scc[u]);
                r_rev[i] = max(r_rev[i], scc[v]);
            }
        }

        int L = r_rev[i] + 1;
        int R = i - 1;
        if (L <= R) {
            add(L, R);
        }
    }

    int ans = 0;
    vector<int> good(n+1, 0);
    for (int i = 0; i < N; i++) {
        if (i > 0) pref[i] += pref[i - 1];
        if (pref[i] == 0) {
            for (auto u : scc_vertices[i]) {
                good[u] = 1;
                ans++;
            }
        }
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++)
        if (good[i]) cout << i << " ";
    

    cout << "\n";
}