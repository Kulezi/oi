// Generatorka do zadania 'Strajki' z II etapu XXIV OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a,b)(rng);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(1, 10);
    cout << n  << endl;
    for (int i = 2; i <= n; i++) {
        cout << R(1, i-1) << " " << i << "\n";
    }

    int m = R(1, 10);
    cout << m << endl;
    vector<int> strajk(n+1, 0);
    while (m--) {
        int x = R(1, n);
        strajk[x] = 1 - strajk[x];
        if (strajk[x]) cout << x << "\n";
        else cout << -x << "\n";
    }
}
