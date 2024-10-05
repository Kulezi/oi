// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(wynik * n * (n+m))
// Złożoność pamięciowa: O(n + m)
// Punkty: ??? (brut)

#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1'000'000'000;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n+1), b(m+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    if (n > m) {
        swap(n, m);
        swap(a, b);
    }

    int max_ans = n / 2;
    int ans = 0;
    vector<int> dp(n+1, INF), next_dp(n+1, INF);
    dp[0] = 0;
    for (int wynik = 0; wynik <= max_ans; wynik++) {
        for (int i = 0; i < n; i++) { // TODO: wlicz n do wyniku.
            int a_l = i+1;
            int ch = a[a_l];

            // Jakbym nie wziął tej literki, to wynik mi się nie zmieni, a prefiks zwiększy o 1.
            if (dp[i + 1] > dp[i]) dp[i + 1] = dp[i];

            // Jakbym wziął tę literkę, to w słowie a następną będę mógł wziąć dopiero po jej nastepnym wystąpieniu (biorę ją i najbliższą na prawo).
            int a_r = a_l+1;
            while (a_r <= n && a[a_r] != ch) a_r++;
            if (a_r > n) continue;

            int b_l = dp[i]+1;
            while (b_l <= m && b[b_l] != ch) b_l++;

            int b_r = b_l+1;
            while (b_r <= m && b[b_r] != ch) b_r++;
            if (b_r > m) continue;

            next_dp[a_r] = min(next_dp[i], b_r);
            ans = wynik+1;
        }

        if (ans == wynik) break;

        swap(dp, next_dp);
        next_dp = vector<int>(n+1, INF);
    }

    cout << 2*ans << "\n";
}