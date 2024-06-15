// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * k)
// Złożoność pamięciowa: O(n)
// Punkty: 64 (upsolve)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MAXN = 100'005;

vector<pair<int,int>> g[MAXN];
int par[MAXN], weight[MAXN];
ll gain[MAXN];

vector<int> ord;
void dfs(int v) {
    if (v != 1) ord.push_back(v);
    for (auto &[u, w] : g[v]) {
        if (u != par[v]) {
            par[u] = v;
            weight[u] = w;
            dfs(u);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;

    long long ans = 0;
    for (int i = 2; i <= n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        ans += 2 * w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    par[1] = -1;
    dfs(1);

    while (k--) {
        int best = 1;
        for (auto u : ord) {
            gain[u] = gain[par[u]] + weight[u];
            if (g[u].size() == 1 && gain[best] < gain[u]) {
                best = u;
            }
        }

        cerr << best << " " << gain[best] << "\n";
        if (gain[best] <= 0) break;
        ans -= gain[best];

        while (best != 1) {
            if (weight[best] > 0) weight[best] *= -1;
            best = par[best];
        }
        
    }

    cout << ans << "\n";
}