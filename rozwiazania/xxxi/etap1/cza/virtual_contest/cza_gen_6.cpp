#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll R(ll a, ll b) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(a, b)(rng);
}

constexpr ll MAXN = 1'000'000, MAXB = 1e18;

int main() {
    ios_base::sync_with_stdio(0);

    int n, k;
    long long a, b;
    // cin >> n >> k >> a >> b;
    n = R(2, MAXN);
    k = R(1, n-1);

    b = R(n + 2, MAXB);
    a = R(n+1, b-1);
    a = max(a, b - 1'000'000 + 1);

    assert(n >= 2);
    assert(n <= 1'000'000);
    assert(n < a);
    assert(a < b);
    assert(b <= (long long)1e18);

    string s;
    while (s.size() < n) s += (char)R('a', 'b');
    cout << n << " " << k << " " << a << " " << b << "\n";
    cout << s << "\n";

}