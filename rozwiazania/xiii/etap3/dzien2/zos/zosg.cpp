// Generatorka testów do zadania 'Zosia' z III etapu XIII OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}


int32_t main() {
    int n = R(1, 100), k = R(max(1, n - 10), n);
    cout << n << " " << k << endl;

    set<pair<int, int>> s;
    int m = R(0LL, min(3'000'000LL, 1LL * n * (n - 1)));
    cout << m << endl;
    while (m--) {
        int a = R(1, n - 1);
        int b = R(a + 1, n);
        if (R(0, 1)) swap(a, b);
        while (s.count({a, b})) {
            a = R(1, n - 1);
            b = R(a + 1, n);
            if (R(0, 1)) swap(a, b);
        }

        s.insert({a, b});

        cout << a << " " << b << endl;
    }
}