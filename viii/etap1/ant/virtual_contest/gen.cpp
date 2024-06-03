#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

constexpr int MAXN = 1'000'000;

int32_t main() {
    cout << R(1, MAXN) << "\n";
}