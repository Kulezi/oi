// Rozwiązanie brutalne do zadania 'FarmerCraft' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n!)
// Złożoność pamięciowa: O(n)
// Punkty: 22 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 500005;
int c[MAXN], sub[MAXN], dp[MAXN];
vector<int> g[MAXN];
void dfs(int v) {
    sub[v] = 1;
    vector<int> sons;
    for (auto u : g[v]) {
        if (!sub[u]) {
            dfs(u);
            sons.push_back(u);
            sub[v] += sub[u];
        }
    }

    sort(sons.begin(), sons.end());

    dp[v] = c[v];

    int mini = 2e9;
    do {
        int mx = 0;
        int sum = 0;
        for (auto u : sons) {
            mx = max(mx, sum + dp[u] + 1);
            sum += 2 * sub[u];
        }
        
        mini = min(mx, mini);
    } while (next_permutation(sons.begin(), sons.end()));

    dp[v] = max(dp[v], mini);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);
    int wynik = max(dp[1], 2 * (n - 1) + c[1]);
    cout << wynik << endl;
}