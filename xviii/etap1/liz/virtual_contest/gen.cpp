#include <bits/stdc++.h>
using namespace std;

int R(int l, int r) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(l, r)(rng);
}

int32_t main() {
    int n = R(1, 10);
    int m = R(1, 10);

    cout << n << " " << m << "\n";
    for (int i = 1; i <= n; i++) {
        cout << (R(0, 1) ? "T" : "W");
    }

    cout << "\n";

    while(m--) {
        cout << R(1, 20) << "\n";
    }
}