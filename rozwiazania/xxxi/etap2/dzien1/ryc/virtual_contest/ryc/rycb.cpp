// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^d * m * k)
// Punkty: Niesubmitowane, brut do stresstestów.

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXK = 10, MAXN = 10005;
int n, m, d, k;

vector<pair<int, vector<int>>> g[MAXN];

vector<int> ans;

void dfs(int v, int dis, vector<int> miecze) {
    if (v == n) {
        ans = max(ans, miecze);
    }
    
    if (dis == d) return;
    for (auto &[u, rzemieslnik] : g[v]) {
        auto nowe_miecze = miecze;
        for (int i = 0; i < k; i++) {
            if (nowe_miecze[i] < rzemieslnik[i]) nowe_miecze[i] = rzemieslnik[i];
        }

        dfs(u, dis+1, nowe_miecze);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m >> d >> k;

    ans = vector<int>(k, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        vector<int> rzemieslnik(k, 0);
        for (auto &j : rzemieslnik) cin >> j;

        g[u].emplace_back(v, rzemieslnik);
        g[v].emplace_back(u, rzemieslnik);

    }

    dfs(1, 0, ans);
    for (auto i : ans) cout << i <<  " ";
    cout << "\n";
}