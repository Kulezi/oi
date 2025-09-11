// Generatorka testów do zadania 'Przekaźniki telekomunikacyjne' z II etapu XXV OI.
// Autor: Paweł Putra

#include <chrono>
#include <iostream>
#include <random>
#include <set>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}
constexpr int MAX_S = 100000, MAX_A = 100000;

int32_t main() {
    int n = R(2, 300000);
    int m = R(1, 10);
    cout << n << " " << m << endl;

    set<int> aktywne;
    for (int i = 1; i <= m; i++) {
        int x = R(1, n);
        if (R(0, 2))
            cout << "Z " << x << " " << R(x, n) << "\n";
        else if (aktywne.count(x)) {
            aktywne.erase(x);
            cout << "U " << x << "\n";
        } else {
            aktywne.insert(x);
            cout << "P " << x << " " << R(1, MAX_S) << " " << R(1, MAX_A) << "\n";
        }
    }
}