// Rozwiązanie do zadania 'Ptaszek' z II etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
int n;
constexpr int MAXN = 1'000'005, INF = MAXN;
int d[MAXN];

struct kmax {
    list<int> q;
    void push(int i) {
        while (!q.empty() && d[q.back()] <= d[i]) q.pop_back();
        q.push_back(i);
    }

    void pop(int i) {
        if (!q.empty() && q.front() == i) q.pop_front();
    }

    int max_idx() { return q.front(); }
    void clear() { q.clear(); }
};

// Kolejki minimów trzymające indeksy na których wartość dp występuje w ciągu d w okienku długości
// k.
kmax kmax_dp[MAXN];
void solve(int k) {
    vector<int> dp(n + 1, INF);
    deque<int> kmin = {1};
    dp[1] = 0;
    kmax_dp[0].push(1);
    for (int i = 2; i <= n; i++) {
        // Wylicz dp.
        int min_dp = dp[kmin.front()];
        int min_dp_max_val = d[kmax_dp[min_dp].max_idx()];

        // Wynik zwiększy się o 1 od minimalnego dp tylko jak z wszystkich pozycji z takim dp trzeba
        // wylecieć do góry.
        dp[i] = min_dp + (min_dp_max_val > d[i] ? 0 : 1);

        while (!kmin.empty() && dp[kmin.back()] >= dp[i]) kmin.pop_back();
        kmin.push_back(i);
        kmax_dp[dp[i]].push(i);
        if (i - k >= 1) {
            if (kmin.front() == i - k) kmin.pop_front();
            kmax_dp[dp[i - k]].pop(i - k);
        }
    }

    for (int i = n - k; i <= n; i++) kmax_dp[dp[i]].clear();
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