// Generatorka testów do zadania 'Pionek' z I etapu XXV OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(1, 1000);
    cout << n << "\n";

    while(n--) {
        cout << R(-10, 10) << " " << R(-10, 10) << "\n";
    }
}