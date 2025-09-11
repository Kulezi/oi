// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(p*log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr ll MAXN = 4e17;
vector<ll> f = {0, 1};

int rozloz(ll n) {
    if (n == 0) return 0;
    ll mini = n;
    for (ll i : f) {
        ll m = llabs(n - i);
        mini = min(mini, m);
    }

    return 1 + rozloz(mini);
}

int32_t main() {
    while (f.back() < MAXN) f.push_back(f.back() + f[f.size()-2]);
    reverse(f.begin(), f.end());

    int p;
    cin >> p;

    while (p--) {
        ll n;
        cin >> n;

        cout << rozloz(n) << "\n";
    }

}