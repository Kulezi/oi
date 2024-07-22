// Generatorka testów do zadania 'Autostrady' z II etapu X OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(2, 100);

    int m = R(1, n * (n - 1) / 2);
    cout << n << " " << m << endl;

    set<pair<int,int>> edges;
    while (m--) {
        int a = R(1, n - 1);
        int b = R(a + 1, n);
        while (edges.count({a, b})) {
            a = R(1, n - 1);
            b = R(a+1, n);
        }

        edges.insert({a, b});
        cout << a << " " << b << endl;
    }
}