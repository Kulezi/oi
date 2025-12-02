// Rozwiązanie zadania 'Sabotaż' z I Etapu XXIV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n).
// Złożoność pamięciowa: O(n).

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
constexpr int MAXN = 500'005;
vector<int> g[MAXN];
// dp[v] = max x, takie że całe poddrzewo v mogłoby się zbuntować.
double dp[MAXN];
int s[MAXN];

void dfs(int v) {
    for (auto syn : g[v]) {
        dfs(syn);
        s[v] += s[syn] + 1;
    }

    // Jeśli jestem liściem to dp[v] = 0,
    // a jak nie, to mój syn mógł być sabotażystą.
    if (s[v] > 0) dp[v] = 1.0 / s[v];

    // Mój syn byłby zwykłym buntownikiem.
    for (auto syn : g[v]) {
        dp[v] = max(dp[v], min(dp[syn], (double)(s[syn] + 1) / s[v]));
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    double wynik = 0;
    for (int v = 1; v <= n; v++) {
        if (s[v] >= k)
            wynik = max(wynik, dp[v]);
    }

    cout << fixed << setprecision(9) << wynik << "\n";
}
