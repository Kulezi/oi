// Generatorka testów do zadania 'Pakowanie plecaka' z II etapu XXVIII OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    
    int n = R(1, 1000);
    cout << n << "\n";
    for (int i = 1; i <= n; i++) cout << R(1, 1e9) << " ";
    cout << "\n";
}