// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: ??? (brut)

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'005;
int n, m;


vector<int> bfs(int start, vector<vector<int>> &g) {
    vector<int> vis(n+1, 0);
    vis[start] = 1;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                q.push(u);
            }
        }
    }

    return vis;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;

    vector g(n+1, vector<int>()), grev(n+1, vector<int>());

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        grev[b].push_back(a);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        auto vis1 = bfs(i, g);
        auto vis2 = bfs(i, grev);
        bool good = true;
        for (int j = 1; j <= n; j++) {
            if (!vis1[j] && !vis2[j]) {
                good = false;
                break;
            }
        }

        if (good) ans.push_back(i);
    }

    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }

    cout << "\n";
}