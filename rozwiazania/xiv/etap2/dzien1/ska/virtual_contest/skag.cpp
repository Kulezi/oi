// Generatorka testów do zadania 'Skalniak' z II etapu XIV OI.
// Autor: Paweł Putra
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 2'000'000'000;
int x[MAXN], y[MAXN], m[MAXN];

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
constexpr int MX = 1'000'000'000, GEN_N = 10;
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n = R(2, GEN_N);
    cout << n << "\n";

    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        int x = R(0, MX);
        int y = R(0, MX);
        while (s.count({x, y})) {
            x = R(0, MX);
            y = R(0, MX);
        }

        s.insert({x, y});
        s.insert({y, x});

        cout << x << " " << y << " " << R(1, MX) << "\n";
    }
}
