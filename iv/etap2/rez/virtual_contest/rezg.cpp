#include <bits/stdc++.h>
using namespace std;
constexpr int MAXB = 30005;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(1, 20);
    cout << n << "\n";

    for (int i = 0; i < n; i++) {
        int a = R(1, 30000);
        int b = R(1, 30000);
        if (a > b) swap(a, b);
        cout << a << " " << b << "\n";
    }
    
}