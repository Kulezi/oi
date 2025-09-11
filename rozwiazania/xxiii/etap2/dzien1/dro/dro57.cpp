// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (n + m) / n + m zależnie od podgrupy)
// Złożoność pamięciowa: O(n + m)
// Punkty: 57

// Brut dla pierwszej podgrupy i silnie spójne składowe (SSS) dla drugiej,
// jedyne dobre korzenie muszą być w jedynej SSS, do której nie wchodzi żadna
// krawędź.
#include <bits/stdc++.h>
using namespace std;

namespace brute {
vector<int> bfs(int n, int start, vector<vector<int>> &g) {
    vector<int> vis(n + 1, 0);
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

void solve(int n, int m) {
    vector g(n + 1, vector<int>()), grev(n + 1, vector<int>());

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        grev[b].push_back(a);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        auto vis1 = bfs(n, i, g);
        auto vis2 = bfs(n, i, grev);
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
};  // namespace brute

namespace subtask2 {
constexpr int MAXN = 500'005;
int n, m;

vector<int> g[MAXN], grev[MAXN], cg[MAXN];
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

void solve(int n, int m) {
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        grev[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }

    reverse(ord.begin(), ord.end());
    for (auto i : ord) {
        if (vis[i] != 2) {
            dfs2(i);
            while (!component.empty()) {
                scc[component.back()] = i;
                component.pop_back();
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto j : g[i]) {
            if (scc[i] != scc[j]) st[scc[j]]++;
        }
    }

    vector<int> ans, good_ccs;
    for (int i = 1; i <= n; i++) {
        if (scc[i] == i && st[i] == 0) {
            good_ccs.push_back(i);
        }

        if (st[scc[i]] == 0) ans.push_back(i);
    }

    if (good_ccs.size() == 1) {
        cout << ans.size() << "\n";
        for (auto i : ans) cout << i << " ";
        cout << "\n";
    } else {
        cout << "0\n";
    }

    return;
}
};  // namespace subtask2

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    if (n > 5000) {
        subtask2::solve(n, m);
    } else {
        brute::solve(n, m);
    }
}