// Generatorka testów do zadania 'Ciąg binarny' z II etapu XXXI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<>(a,b)(rng);
}
int32_t main() {

    int n = R(1, 16), m = R(1, 3);
    //int n = 1000000, m = 1000000;
    cout << n << " " << m << "\n";


    const int MX = R(1, 10);

    int S = 0;
    for (int i = 1; i <= n; i++) {
        int d = R(1, MX);
        cout << d << " ";
        S += d;
    }

    cout << "\n";
    while (m--) {
        int l = R(1, S);
        int r = R(l, S);
        int k = R(0, 10);
        cout << l << " " << r << " " << k << "\n";
    }
}
