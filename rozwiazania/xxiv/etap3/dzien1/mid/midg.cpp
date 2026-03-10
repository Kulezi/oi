// Generatorka do zadania 'Midas' z III etapu XXIV Olimpiady Informatycznej.
// Autor: Paweł Putra

#include <vector>
#include <iostream>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <set>
#include <random>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll R(ll a, ll b) {
    return uniform_int_distribution<ll>(a, b)(rng);
}
void solve() {
    int n = 10;
    cout << n << endl;

    vector syn(n+1, vector<int>(2, 0));
    for (int i = 2; i <= n; i++) {
        int ojciec = R(1, i-1);
        int kto = R(0, 1); 
        while (syn[ojciec][kto]) ojciec = R(1, i-1), kto = R(0, 1);
        syn[ojciec][kto] = i;
    }

    for (int i = 1; i <= n; i++) {
        cout << syn[i][0] << " " << syn[i][1] << "\n";
    }

    int z = 1000;
    cout << z << endl;
    while (z--) {
        cout << R(1, n) << " " << R(1, n) << endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int tests = 1;
    while (tests--) {
        solve();
    }
}
