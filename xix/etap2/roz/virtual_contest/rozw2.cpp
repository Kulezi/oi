#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr ll MAXN = 2e18;
vector<ll> f = {0, 1};

map<ll, int> dp;

int rozloz(ll n) {
    if (dp.count(n)) return dp[n];
    ll mini = n;
    ll max_fib_under = 0;
    for (ll i : f) {
        ll m = llabs(n - i);
        mini = min(mini, m);
        if (i <= n) max_fib_under = max(max_fib_under, i);
    }

    return dp[n] = min(1 + rozloz(mini), 1 + rozloz(n - max_fib_under));
}

int32_t main() {
    while (f.back() < MAXN) f.push_back(f.back() + f[f.size()-2]);
    for (auto i : f) {
        // cout << i << "\n";
    }
    reverse(f.begin(), f.end());

    int p;
    cin >> p;

    dp[0] = 0;
    while (p--) {
        ll n;
        cin >> n;

        cout << rozloz(n) << "\n";
    }

}