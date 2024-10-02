// Rozwiązanie brutalne do zadania 'Skalniak' z II etapu XIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n * n)
// Złożoność pamięciowa: O(n)
// Punkty: 10 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 2'000'000'000;
int x[MAXN], y[MAXN], m[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> m[i];
    }

    // Pół obwodu bo dla punktów (0, 0), (10^9, 10^9) obwód to (2 * (10^9 + 10^9)) = 4 * 10^9!
    int min_c = INF;
    int min_mass = INF;
    int min_mask = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int min_x = INF, min_y = INF;
        int max_x = 0, max_y = 0;
        int mass = 0;
        for (int i = 0; i < n; i++) {
            int x_i = x[i];
            int y_i = y[i];
            if (mask >> i & 1) {
                swap(x_i, y_i);
                mass += m[i];
            }

            min_x = min(min_x, x_i);
            max_x = max(max_x, x_i);

            min_y = min(min_y, y_i);
            max_y = max(max_y, y_i);
        }

        int c = max_x - min_x + max_y - min_y;
        if (c < min_c) {
            min_c = c;
            min_mass = mass;
            min_mask = mask;
        } else if (c == min_c && mass < min_mass) {
            min_mass = mass;
            min_mask = mask;
        }
    }

    cout << 2LL * min_c << " " << min_mass << "\n";
    for (int i = 0; i < n; i++) {
        cout << (min_mask >> i & 1);
    }
    cout << "\n";
}
