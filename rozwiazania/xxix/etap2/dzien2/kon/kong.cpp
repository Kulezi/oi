// Generatorka testów do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAX_Q = 8;
string typ = "WZ?";
int32_t main() {
    int q = R(1, MAX_Q);
    cout << q << "\n";    
    int n = 2;
    while (q--) {
        char c = typ[R(0, 2)];
        int x = R(1, n);

        if (c != '?') n++;
        cout << c << " " << x << "\n";
    }
}
