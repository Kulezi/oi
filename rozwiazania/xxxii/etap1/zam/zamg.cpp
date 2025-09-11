#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

const string ALPHA = "189";

int32_t main() {
    // Tylko maxtest mnie interesuje.
    int n = 1000000;
    while (n--) {
        cout << ALPHA[R(0, ALPHA.size() - 1)];
    }
    cout << "\n";
}