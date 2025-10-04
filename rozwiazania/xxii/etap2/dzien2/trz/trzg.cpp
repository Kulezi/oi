// Generatorka do zadania 'Trzy wieże' z II etapu XXII OI.

#include <random>
#include <iostream>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int R(int l, int r) {
    return uniform_int_distribution<>(l, r)(rng);
}

string alpha = "BSC";
int main() {
    int n = R(1, 16);
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        cout << alpha[R(0, 2)];
    }

    cout << "\n";
}
