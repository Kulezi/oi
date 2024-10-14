// Generatorka testów do zadania 'Turystyka' z III etapu XXI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(2, 10);
    int m = R(n - 1, n - 1);

    cout << n << " " << m << endl;
    for (int i = 1; i <= n; i++) cout << R(0, 2) << " ";
    cout << "\n";

    set<pair<int, int>> s;
    for (int i = 2; i <= n; i++) {
        int par = R(1, i - 1);
        cout << par << " " << i << "\n";
        s.insert({par, i});
        m--;
    }

    while (m--) {
        int a = R(1, n - 1);
        int b = R(a + 1, n);
        while (s.count({a, b})) {
            a = R(1, n - 1);
            b = R(a + 1, n);
        }

        cout << a << " " << b << endl;
        s.insert({a, b});
    }
}