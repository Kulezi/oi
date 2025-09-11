#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr ll  MAXN = 4e17;

ll R(ll a, ll b) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}
int32_t main() {
    int p = R(1, 10);
    cout << p << "\n";

    while (p--) {
        cout << R(1, MAXN) << "\n";
    }
}