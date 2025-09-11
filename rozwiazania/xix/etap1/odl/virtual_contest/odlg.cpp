#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_A = 10;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    srand(R(1, INT_MAX));
    int n = R(2, 5);
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << R(1, 10) << "\n";
}