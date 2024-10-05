// Generatorka testów do zadania 'Panele słoneczne' z III etapu XXI OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    int n = R(1, 1000);
    cout << n << endl;
    auto para = [&](int MAX) -> pair<int,int> {
        int a = R(1, MAX);
        int b = R(a, MAX);
        return {a, b};
    };

    while (n--) {
        auto [a, b] = para(1e9);
        auto [c, d] = para(1e9);
        cout << a << " " << b << " " << c << " " << d << endl;
    }
}