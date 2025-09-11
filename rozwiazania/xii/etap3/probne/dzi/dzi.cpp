// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n+m)
// Złożoność pamięciowa: O(n+m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_N = 1'000'005;

vector<int> g[MAX_N];
int fac[MAX_N];

void no() {
    cout << "0\n";
    exit(0);
}

// Zwraca stopień (liczbę krawędzi) wierzchołka.
inline int deg(int v) {
    return (int)g[v].size();
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;

    // Jak mamy więcej niż n-1 krawędzi to na pewno mamy jakiś cykl, czyli ptaszki się zderzą.
    // Dzięki temu wczytamy max 10^6 krawędzi zamiast 10^7.
    if (m > n - 1) no();

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = 1LL * fac[i-1] * i % k;
    }

    int caterpillar_cnt = 0;
    int caterpillar_orderings = 1;
    int isolated_cnt = 0;


    vector<int> vis(n+1, 0);
    vector<int> leaves(n+1, 0);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        if (deg(i) == 0) {
            // Wierzchołek izolowany.
            isolated_cnt++;
            continue;
        }

        queue<int> q;
        vector<int> not_leaves;
        auto push = [&](int v) {
            vis[v] = 1;
            q.push(v);
        };

        int n_vertices = 0, degree_sum = 0;
        push(i);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            degree_sum += deg(v);
            ++n_vertices;
            if (deg(v) != 1) not_leaves.push_back(v);
            for (auto u : g[v]) {
                if (deg(v) == 1) leaves[u]++;
                if (!vis[u]) push(u);
            }
        }

        int n_edges = degree_sum / 2;
        if (n_edges != n_vertices - 1) no();

        int path_len = not_leaves.size();
        
        // Na ile sposobów można rozłożyć liście gąsienicy. 
        int orderings_within_path = 1;
        for (auto v : not_leaves) {
            // Graf nie jest gąsienicą - zawsze będą dwie przecinajace się krawędzie.
            if (deg(v) - leaves[v] > 2) no();
            orderings_within_path = 1LL * orderings_within_path * fac[leaves[v]] % k;
        }

        // Na ile sposobów można rozłożyć końce ścieżki między dwa drzewa.
        int start_end_orderings = 1;
        if (path_len < 2) {
            start_end_orderings = 2;
        } else {
            start_end_orderings = 4;
        }

        
        caterpillar_cnt++;
        caterpillar_orderings = 1LL * caterpillar_orderings * start_end_orderings * orderings_within_path % k;
    }

    // Na ile sposobów można włożyć wierzchołki izolowane do każdego z ułożeń gąsienic.
    int isolated_orderings = 1;
    int caterpillar_vertex_cnt = n - isolated_cnt;
    int holes = caterpillar_vertex_cnt+2;
    for (int i = 0; i < isolated_cnt; i++) {
        isolated_orderings = 1LL * isolated_orderings * (holes + i) % k;
    }

    int ans = 1LL * caterpillar_orderings * isolated_orderings % k;

    // Gąsienice mogą być ułożone na drzewach w dowolnej kolejności.
    ans = 1LL * ans * fac[caterpillar_cnt] % k;
    
    cout << ans << "\n";
}