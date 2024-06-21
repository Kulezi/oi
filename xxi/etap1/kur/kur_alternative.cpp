// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n * log(n))
// Punkty:  (upsolve)

// Dla każdego zapytania wyłuskujemy lidera bit po bicie używając sum prefiksowych.
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

constexpr int B = 19, MAXN = 1000005;
int pref[B+1][MAXN];
vector<int> occ[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        occ[x].push_back(i);
        for (int b = 0; b < B; b++) {
            pref[b][i] = pref[b][i-1] + (x >> b & 1);
        }
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        
        int candidate = 0;
        int len = r - l + 1;
        for (int b = 0; b < B; b++) {
            int cnt_set = pref[b][r] - pref[b][l-1];
            if (2 * cnt_set > len) candidate += 1 << b;
        }

        
        int cnt = upper_bound(all(occ[candidate]), r) - lower_bound(all(occ[candidate]), l);
        if (2 * cnt <= len) candidate = 0;
        cout << candidate << "\n";
    }

}