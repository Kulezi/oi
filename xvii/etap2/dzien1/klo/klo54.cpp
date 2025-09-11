// Rozwiązanie do zadania 'Klocki' z II etapu XVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n) * k)
// Złożoność pamięciowa: O(n)
// Punkty: 54 (upsolve)

#include <iostream>
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
int n, m;
int t[MAXN];
ll sum[MAXN], nadmiar_pref[MAXN], nadmiar_suf[MAXN];

int solve(int k) {
    ll nadmiar = 0;

    for (int i = 1; i <= n; i++) {
        nadmiar_suf[i] = nadmiar;
        nadmiar = max(0LL, nadmiar + t[i] - k);
    }

    nadmiar = 0;
    for (int i = n; i >= 1; i--) {
        nadmiar_suf[i] = nadmiar;
        nadmiar = max(0LL, nadmiar + t[i] - k);
    }

    auto check = [&](int len) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = (l + len - 1);
            if (nadmiar_pref[l] + nadmiar_suf[r] + sum[r] - sum[l - 1] >= 1LL * k * len)
                return true;
        }

        return false;
    };

    int lo = 0, hi = n;
    while (lo < hi) {
        int len = (lo + hi + 1) / 2;
        if (check(len))
            lo = len;
        else
            hi = len - 1;
    }

    return lo;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i - 1] + t[i];
    }

    while (m--) {
        int k;
        cin >> k;
        cout << solve(k) << " ";
    }

    cout << "\n";
}