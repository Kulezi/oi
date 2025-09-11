// Rozwiązanie brutalne do zadania 'Pakowanie plecaka'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 38 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
constexpr ll INF = 1e18;

int n;
ll dp[MAXN][2];
int w[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    int layer = 0;
    for (int i = 1; i <= n; i++) dp[i][layer] = INF;
    for (int i = n; i >= 1; i--) {
        layer = 1 - layer;
        for (int cnt = 1; cnt <= n; cnt++) {
            if (dp[cnt][1 - layer] < w[i]) dp[cnt][layer] = dp[cnt][1 - layer];
            else {
                dp[cnt][layer] = dp[cnt-1][1 - layer] + w[i];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dp[i][layer] << " ";
    }

    cout << "\n";
}