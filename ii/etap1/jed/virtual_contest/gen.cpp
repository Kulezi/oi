#include <bits/stdc++.h>
using namespace std;

constexpr int MAXT = 20000;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int tests = MAXT;
    cout << tests << "\n";
    for (int tc = 1; tc <= tests; tc++) {
        cout << tc << "\n";
    }
}