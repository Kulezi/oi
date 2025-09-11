// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^4)
// Złożoność pamięciowa: O(n^2)
// Punkty: 50 (upsolve)

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005;
vector<int> g[MAXN];
int who[MAXN][MAXN];

void add_edge(int a, int b, int face) {
    if (a > b) swap(a, b);
    if (!who[a][b]) {
        who[a][b] = face + 1;
    } else {
        g[face].push_back(who[a][b] - 1);
        g[who[a][b] - 1].push_back(face);
    }
}

int32_t main() {
    int n;
    cin >> n;

    int n_triangles = n - 2;
    for (int i = 0; i < n_triangles; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, i);
        add_edge(b, c, i);
        add_edge(a, c, i);
    }

    // Dla zbioru wierzchołków drzewa daje rozmiar drzewa indukowanego przez
    // ścieżki między nimi.
    auto brute = [&](vector<int> roots) -> int {
        vector<int> st(n_triangles, 0), bad(n_triangles, 0);
        queue<int> q;
        for (auto root : roots) bad[root] = 1;
        for (int t = 0; t < n_triangles; t++) {
            st[t] = (int)g[t].size();
            if (st[t] == 1 && !bad[t]) {
                bad[t] = 1;
                q.push(t);
            }
        }

        int res = n_triangles;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            res--;
            for (auto v : g[u]) {
                if (!bad[v]) {
                    st[v]--;
                    if (st[v] == 1 || st[v] == 0) {
                        bad[v] = 1;
                        q.push(v);
                    }
                }
            }
        }

        return res;
    };

    // Możemy wybrać max 3 wierzchołki triangulacji jako wierzchołki trójkątów.
    // Zamiast wybierać wierzchołki wielokąta, możemy po prostu wybierać
    // trójkąty z triangulacji. Ominiemy tak też odejmowanie 3 dodatkowych
    // wierzchołków z wyniku.
    int ans = 0;
    for (int i = 0; i < n_triangles; i++) {
        ans = max(ans, brute({i}));
        for (int j = i + 1; j < n_triangles; j++) {
            ans = max(ans, brute({i, j}));
            for (int k = j + 1; k < n_triangles; k++) {
                ans = max(ans, brute({i, j, k}));
            }
        }
    }

    cout << ans << "\n";
}
