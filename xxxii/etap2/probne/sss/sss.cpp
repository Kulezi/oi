// Rozwiązanie do zadania 'Sekretna siatka szpiegowska' z II etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

// Wybieramy k korzeni minimalizujących sumę po wszystkich wierzchołkach v dist(v) * deg(v).
// Intuicja: Im później podpięty wierczhołek, tym niższy jego oczekiwany stopień, a wyższa oczekiwana odległość od korzenia.
// Eksperymentalnie wychodzi ~90% trafień na 4-tej grupie testów.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
vector<int> g[MAXN];
ll suma[MAXN], sub[MAXN];
ll dfs(int v, int par, int d) {
    sub[v] = g[v].size();
    ll res = g[v].size() * d;
    for (auto u : g[v]) {
        if (u != par) {
            res += dfs(u, v, d + 1);
            sub[v] += sub[u];
        }
    }
    return res;
}

void reroot(int v, int par, ll sum) {
    suma[v] = sum;
    for (auto u : g[v]) {
        if (u != par) {
            reroot(u, v, sum - sub[u] + (sub[1] - sub[u]));
        }
    }
}

int git = 0;

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) g[i].clear(), suma[i] = 0, sub[i] = 0;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<pair<ll, int>> ord;

    ll s1 = dfs(1, -1, 0);
    reroot(1, -1, s1);
    for (int i = 1; i <= n; i++) {
        ord.emplace_back(suma[i], i);
    }

    sort(ord.begin(), ord.end());
    ord.resize(k);
    for (auto i : ord) {
        cout << i.second << " ";
        if (i.second == 1) git++;
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        solve();
    }
}
