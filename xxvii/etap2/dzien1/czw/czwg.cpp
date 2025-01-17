// Generatorka testów do zadania 'Drzewo czwórkowe' z II etapu XXVII OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

void gen(int lx, int rx, int ly, int ry) {
    if (lx == rx || ly == ry) {
        cout << R(0, 1);
    } else {
        if (R(0, 3))
            cout << R(0, 1);
        else {
            cout << 4;
            int mx = (lx + rx) / 2;
            int my = (ly + ry) / 2;
            gen(lx, mx, ly, my);
            gen(mx + 1, rx, ly, my);
            gen(lx, mx, my + 1, ry);
            gen(mx + 1, rx, my + 1, ry);
        }
    }
}

int32_t main() {
    int m = R(2, 10);
    cout << m << endl;
    gen(1, 1 << m, 1, 1 << m);
    cout << endl;
}