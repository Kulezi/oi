// Generatorka testów do zadania 'Okropny wiersz' z II etapu XIX OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(1, 10);
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << (char)R('a', 'b');
    }

    cout << "\n";
    int q = R(1, 10);
    cout << q << "\n";
    while(q--) {
        int l = R(1, n);
        int r = R(l, n);
        cout << l << " " << r << "\n";
    }
}