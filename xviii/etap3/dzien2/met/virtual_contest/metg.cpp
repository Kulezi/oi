#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAX = 1'000'000'000;
int32_t main() {
    int n = R(1, 300000);
    int m = R(1, 10);
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; i++) cout << R(1, n) << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++) cout << R(MAX, MAX) << " ";
    cout << "\n";
    int k = R(1, 300000);
    cout << k << endl;
    for (int i = 1; i <= k; i++) {
        
        cout << R(1, 1) << " " << R(1, m) << " " << R(1, MAX) << "\n";
    }
}