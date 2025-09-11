// Rozwiązanie brutalne do zadania 'Sprawiedliwy podział' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^n * n)
// Złożoność pamięciowa: O(n)
// Punkty: 20 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 500005, INF = 2'000'000'000;
int n;
int a[MAXN], b[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int mask = 0; mask < (1 << n); mask++) {
        int min_a = INF, min_b = INF;
        ll sum_a = 0, sum_b = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                // Ten przedmiot trafia do Bitka.
                sum_a -= a[i];
                sum_b += b[i];
                min_a = min(min_a, a[i]);
            } else {
                sum_a += a[i];
                sum_b -= b[i];
                min_b = min(min_b, b[i]);
            }
        }

        if (sum_a + min_a >= 0 && sum_b + min_b >= 0) {
            for (int i = 0; i < n; i++) {
                cout << (mask >> i & 1) << " ";
            }
            cout << "\n";
            return 0;
        }
    }

    assert(false);
    cout << "-1\n";
}