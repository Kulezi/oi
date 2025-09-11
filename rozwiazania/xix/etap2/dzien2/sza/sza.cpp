// Rozwiązanie do zadania 'Szatnia' z II etapu XIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(p * log(p) + n * max(k_j))
// Złożoność pamięciowa: O(n + max(k_j))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAX_K = 100000, INF = 2'000'000'000;

struct Query {
    int m, k, s;
    int end() { return m + s; }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<tuple<int, int, int>> items;
    for (int i = 1; i <= n; i++) {
        int c, a, b;
        cin >> c >> a >> b;
        items.emplace_back(b, a, c);
    }

    items.emplace_back(0, INF, 1);
    sort(all(items));
    reverse(all(items));

    int p;
    cin >> p;
    vector<Query> queries(p);
    for (int i = 0; i < p; i++) {
        auto &[m, k, s] = queries[i];
        cin >> m >> k >> s;
    }

    vector<int> ord(p), ans(p, 0);
    iota(all(ord), 0);
    sort(all(ord), [&](int l, int r) { return queries[l].end() > queries[r].end(); });

    // dp[c] = minimalne a_i, takie że istnieje zbiór przedmiotów o sumarycznym koszcie c,
    // spośród przedmiotów o czasie odbioru >= b.
    vector<int> dp(MAX_K + 1, INF);
    dp[0] = -INF;

    int j = 0;
    for (auto &[b, a, c] : items) {
        while (j < p && queries[ord[j]].end() >= b) {
            int q = ord[j];
            ans[q] = (dp[queries[q].k] <= queries[q].m);
            j++;
        }

        for (int i = MAX_K; i >= c; --i) {
            dp[i] = min(dp[i], max(dp[i - c], a));
        }
    }

    for (auto i : ans) cout << (i ? "TAK\n" : "NIE\n");
}