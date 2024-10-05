// Rozwiązanie brutalne do zadania 'Ptaszek' z II etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 33 (upsolve)

#include <bits/stdc++.h>
using namespace std;
int n;
constexpr int MAXN = 1'000'005, INF = MAXN;
int d[MAXN];

void solve(int k) {
    vector<int> dp(n + 1, INF);
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = max(i - k, 0); j < i; j++) {
            dp[i] = min(dp[i], dp[j] + (d[j] > d[i] ? 0 : 1));
        }
    }

    cout << dp[n] << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        solve(k);
    }
}