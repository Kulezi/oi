// Generatorka testów do zadania 'Kolacje' z II etapu XXVI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
constexpr int MAXN = 100000, MAXR = 300, MAXQ = 1, MAXW = 1000000;
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = R(1, MAXN), r = R(1, MAXR);
    cout << n << " " << r << "\n";

    for (int i = 1; i <= n; i++) cout << R(1, r) << " ";
    cout << "\n";
    for (int i = 2; i <= n; i++) {
        cout << R(1, i-1) << " " << i << " " << R(1, MAXW) << "\n";
    }

    int q = R(1, MAXQ);
    cout << q << "\n";
    while (q--) {
        cout << R(1, n) << " " << R(1, n) << " " << R(1, r) << "\n";
    }
}