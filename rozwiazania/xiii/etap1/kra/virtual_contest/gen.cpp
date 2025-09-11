#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 3000, MAXM = 3000, MAXA = 1000000000;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = R(1, MAXN);
    int m = R(1, MAXM);

    cout << n << " " << m << "\n";
    for (int i = 1; i <= n; i++) {
        cout << R(1, MAXA) << " ";
        // cout << n << " ";
    }

    cout << "\n";
    for (int i = 1; i <= m; i++) {
        cout << R(1, MAXA) << " ";
        // cout << n << " ";

    }

    cout << "\n";
}