#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAX = 1'000'000'000;
int32_t main() {
    int n = 1;
    int m = 300000;
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; i++) cout << 1 << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++) cout << MAX << " ";
    cout << "\n";
    int k = R(1, 300000);
    cout << k << endl;
    for (int i = 1; i <= k; i++) {
        
        cout << 2 << " " << 1 << " " << MAX << "\n";
    }
}