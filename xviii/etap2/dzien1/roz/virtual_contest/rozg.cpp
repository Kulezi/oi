#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = 1000000;
    cout << n << "\n";

    for (int i = 1; i <= n; i++) {
        cout << (char)(i%26 + 'a');
    }
    cout << "\n";
}