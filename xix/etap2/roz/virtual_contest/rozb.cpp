#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr ll MAXN = 1e18;
vector<ll> f = {0, 1};

map<ll, int> dp;

ll states = 0;
int rozloz(ll n) {
    if (dp.count(n)) return dp[n];
    states++;
    dp[n] = n;
    for (auto i : f) {
        ll m = llabs(n - i);
        if (m < n) {
            dp[n] = min(dp[n], 1 + rozloz(m));
        }
    }

    return dp[n];
}

int32_t main() {
    while (f.back() < MAXN) f.push_back(f.back() + f[f.size()-2]);
    reverse(f.begin(), f.end());

    int p;
    cin >> p;

    while (p--) {
        int n;
        cin >> n;

        cout << rozloz(n) << "\n";
    }

    cerr << states << "\n";
}