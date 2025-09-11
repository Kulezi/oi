#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(2, 10), m = R(1, n * (n-1));
    cout << n << " " << m << "\n";

    set<pair<int,int>> edges;
    while (m--) {
        int a = 1, b = 2;
        while (edges.count({a, b})) {
            a = R(1, n-1);
            b = R(a+1, n);
            if (R(0, 1)) swap(a, b);
        }

        edges.insert({a, b});
    }

    for (auto [a, b] : edges) {
        cout << a << " " << b << "\n";
    }
}