// Rozwiązanie do zadania 'Meteory'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + k * m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 27 (upsolve)

#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using ll = long long;

#define int ll
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    vector<int> country(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> country[i];
    }

    vector<int> need(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> need[i];
    }

    int k;
    cin >> k;
    vector<ll> sum(n + 1, 0), ans(n + 1, 0);
    for (int i = 1; i <= k; i++) {
        int l, r, delta;
        cin >> l >> r >> delta;

        for (int j = l;; j++) {
            if (j > m) j = 1;
            if (sum[country[j]] < need[country[j]]) {
                sum[country[j]] += delta;
                ans[country[j]] = i;
            }

            if (j == r) break;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (sum[i] < need[i])
            cout << "NIE\n";
        else
            cout << ans[i] << "\n";
    }
}