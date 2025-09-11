#include <bits/stdc++.h>
using namespace std;

void solve(int tc) {
    int n;
    cin >> n;

    for (int mask = 1; mask < (1 << 30); mask++) {
        string liczba = "";
        int reszta = 0;
        for (int i = 29; i >= 0; i--) {
            reszta *= 10;
            if (mask >> i & 1) {
                liczba += "1";
                reszta++;
            } else if (!liczba.empty()) {
                liczba += "0";
            }
            reszta %= n;
        }

        if (reszta == 0) {
            cout << liczba << "\n";
            return;
        }
    }

    cout << "BRAK\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int tests;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        solve(tc);
    }
}