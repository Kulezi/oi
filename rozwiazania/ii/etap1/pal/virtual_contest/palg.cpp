// Generatorka testów do zadania 'Palindromy' z I etapu II OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    int n = R(1, 10) * 2;
    while (n > 0) {
        string s;
        int len = R(1, n / 2);
        for (int i = 1; i <= len; i++) s += (char)R('a', 'z');
        for (int i = len - 1; i >= 0; i--) s += s[i];
        cout << s;

        n -= len * 2;
    }

    cout << "\n";
}