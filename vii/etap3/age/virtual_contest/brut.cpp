#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 251, MAXD = MAXN * MAXN;

vector<int> g[MAXN];
int dis[MAXN][MAXN];
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

    queue<pair<int, int>> q;
    q.push({p1, p2});
    dis[p1][p2] = 1;
    while (!q.empty()) {
        int u = q.front().first;
        int v = q.front().second;
        q.pop();

        if (u == v) {
            cout << dis[u][v] - 1 << "\n";
            return 0;
        }
        
        for (auto un : g[u]) {
            for (auto vn : g[v]) {
                if (!dis[un][vn]) {
                    dis[un][vn] = dis[u][v] + 1;
                    q.push({un, vn});
                }
            }
        }
    }

    cout << "NIE\n";
}
