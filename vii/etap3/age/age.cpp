// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3).
// Punkty: 100 (upsolve).


#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 251, MAXD = MAXN * MAXN;

vector<int> g[MAXN];
int dis[MAXN][MAXN][2];
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int p1, p2;
    cin >> p1 >> p2;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    queue<pair<int, pair<int,int>>> q;
    q.push({p1, {p2, 0}});
    dis[p1][p2][0] = 1;
    while (!q.empty()) {
        int u = q.front().first;
        int v = q.front().second.first;
        int w = q.front().second.second;
        q.pop();

        if (u == v && w == 0) {
            cout << dis[u][v][w] / 2 << "\n";
            return 0;
        }
        

        if (w == 0) {
            for (auto un : g[u]) {
                if (!dis[un][v][1 - w]) {
                    dis[un][v][1 - w] = dis[u][v][w] + 1;
                    q.push({un, {v, 1 - w}});
                }
            }
        } else {
            for (auto vn : g[v]) {
                if (!dis[u][vn][1 - w]) {
                    dis[u][vn][1 - w] = dis[u][v][w] + 1;
                    q.push({u, {vn, 1 - w}});
                }
            }
        }
    }

    cout << "NIE\n";
}
