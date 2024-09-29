// Generatorka testów do zadania 'FarmerCraft' z III etapu XXI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    int n = R(1, 10);
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        cout << R(1, 10) << " ";
    }
    cout << "\n";

    for (int i = 2; i <= n; i++) {
        cout << R(1, i - 1) << " " << i << "\n";
    }
}