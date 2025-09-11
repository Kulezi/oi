// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^k * (n + m) * k)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = " << x << " ";
#define n() cerr << endl;
using namespace std;

constexpr int MAXK = 10, MAXN = 10005, INF = 1'000'000'000;

vector<pair<int, vector<int>>> g[MAXN];
vector<pair<int, int>> g2[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, M, d, k;

    cin >> n >> M >> d >> k;

    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        vector<int> rzemieslnik(k, 0);
        for (auto &j : rzemieslnik) cin >> j;

        g[u].emplace_back(v, rzemieslnik);
        g[v].emplace_back(u, rzemieslnik);
        g2[u].emplace_back(v, 0);
        g2[v].emplace_back(u, 0);
    }

    int full = 0;
    for (int bit = 0; bit < k; bit++) {
        // Liczę bfs odległości do każdej pary (wierzchołek, maska).
        auto bfs = [&](int start) {
            vector dis(n + 1, vector((1 << bit), INF));
            queue<pair<int, int>> q;
            dis[start][0] = 0;
            q.push({start, 0});
            while (!q.empty()) {
                auto [u, m] = q.front();
                q.pop();
                for (auto [v, w] : g2[u]) {
                    int new_m = m | w;
                    if (dis[v][new_m] > dis[u][m] + 1) {
                        dis[v][new_m] = dis[u][m] + 1;
                        q.push({v, new_m});
                    }
                }
            }

            // Zmieniam definicję dist[u][m] = min dlugosc sciezki z maską m.
            // na dist[u][m] = min dlugosc sciezki z maską która jest nadzbiorem m
            // Robię to propagując od największych masek gasząc po jednym
            // bicie na raz.
            for (int m = full; m >= 0; m--) {
                for (int b = 0; b < bit; b++) {
                    if (m >> b & 1) {
                        int new_m = m ^ (1 << b);
                        for (int u = 1; u <= n; u++) {
                            if (dis[u][m] < dis[u][new_m]) {
                                dis[u][new_m] = dis[u][m];
                            }
                        }
                    }
                }
            }

            return dis;
        };

        auto dis_1 = bfs(1);
        auto dis_n = bfs(n);

        // Dla każdej krawędzi sprawdzam, czy jestem w stanie otrzymać
        // pełną maskę bez bitów, które podpala mi krawędź.
        int mx = 0;
        for (int u = 1; u <= n; u++) {
            for (int idx = 0; idx < g[u].size(); idx++) {
                auto [v, w] = g[u][idx];
                auto [_, m_edge] = g2[u][idx];
                for (int m_uw = 0; m_uw <= full; m_uw++) {
                    int m_vw = full ^ m_uw;
                    // Gasimy w obu maskach bity, które zapewnia krawędź.
                    int m_u = m_uw ^ (m_uw & m_edge);
                    int m_v = m_vw ^ (m_vw & m_edge);
                    if (dis_1[u][m_u] + dis_n[v][m_v] + 1 <= d) {
                        mx = max(mx, w[bit]);
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int idx = 0; idx < g[i].size(); idx++) {
                // Wyliczam wartości krawędzi znając już wartość tego bitu.
                if (g[i][idx].second[bit] >= mx) {
                    g2[i][idx].second |= (1 << bit);
                }
            }
        }

        full |= (1 << bit);

        cout << mx << " ";
    }

    cout << "\n";
}