// Generatorka testów do zadania 'Korale'.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    int n = R(1, 200);
    cout << n << endl;
    int limit = R(1, 10);
    for (int i = 1; i <= n; i++) {
        cout << R(1, limit) << " ";
    }

    cout << '\n';
}