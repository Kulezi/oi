// Generatorka testów do zadania 'Ptaszek' z II etapu XXI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(2, 1000);
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        cout << R(1, 100) << " ";
    }
    cout << "\n";

    int q = R(1, 25);
    cout << q << endl;
    while (q--) {
        cout << R(1, n - 1) << endl;
    }
}