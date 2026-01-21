// Generatorka testów do zadania 'Logistyka' z II etapu XXII OI.
// Autor: Paweł Putra
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int R(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}
string alpha = "UZ";
int32_t main() {
    constexpr int M6 = 1'000'000;
    constexpr int M3 = 1'000;
    int n = M3, m = M3;
    cout << n << " " << m << "\n";

    while (m--) {
        cout << alpha[R(0, 1)] << " " << R(1, n) << " " << R(1, 1'000'000'000) << "\n";
    }
}
