// Rozwiązanie do zadania 'Przedsięwzięcie'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> t(n + 2, 0), in(n + 2, 0), out(n + 2, 0);
    vector gin(n + 2, vector<int>()), gout(n + 2, vector<int>());
    auto add_edge = [&](int u, int v) {
        gout[u].push_back(v);
        gin[v].push_back(u);
        out[u]++;
        in[v]++;
    };

    for (int u = 1; u <= n; u++) {
        int k;
        cin >> t[u] >> k;

        for (int i = 1; i <= k; i++) {
            int v;
            cin >> v;
            add_edge(v, u);
        }
    }

    vector<int> color(n + 1, 0);
    auto has_cycle = [&](int v, auto &&self) -> bool {
        color[v] = 1;
        bool res = false;
        for (auto u : gin[v]) {
            if (!color[u])
                res |= self(u, self);
            else if (color[u] == 1)
                return true;
        }

        color[v] = 2;
        return res;
    };

    for (int u = 1; u <= n; u++) {
        if (!color[u] && has_cycle(u, has_cycle)) {
            cout << "CYKL\n";
            return 0;
        }
    }

    auto longest_paths = [&](auto &g, auto &deg) -> vector<ll> {
        vector<ll> d(g.size(), 0);
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!deg[u]) q.push(u);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            d[u] += t[u];
            for (auto v : g[u]) {
                deg[v]--;
                d[v] = max(d[u], d[v]);
                if (deg[v] == 0) q.push(v);
            }
        }

        return d;
    };

    auto din = longest_paths(gout, in);
    auto dout = longest_paths(gin, out);

    ll longest_path = *max_element(din.begin(), din.end());
    cout << longest_path << "\n";
    int q;
    cin >> q;
    while (q--) {
        int m, d;
        cin >> m >> d;

        ll ile = din[m] + dout[m] - t[m] + d;
        if (ile > longest_path)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}