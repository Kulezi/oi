// Rozwiązanie brutalne do zadania 'Klocki' z III etapu XIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(max(a_i)))
// Złożoność pamięciowa: O(max(a_i))
// Punkty: 63 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int MAX_A = 1'000'005, MAX_N = 100'005;
vector<int> occ[MAX_A];
pii mx[MAX_A * 4];
int from[MAX_N];
int a[MAX_N];
pii get_max(int l, int r) {
    pii res = {0, 0};
    for (int i = l; i <= r; i++) {
        res = max(res, mx[i]);
    }

    return res;
}

void put(int pos, int val, int idx) { mx[pos] = {val, idx}; }

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        occ[a[i]].push_back(i);
    }

    for (int i = 1; i < MAX_A; i++) {
        reverse(occ[i].begin(), occ[i].end());
        for (auto j : occ[i]) {
            int r = j - i;
            if (r < 0) continue;
            auto [res, f] = get_max(0, r);

            from[j] = f;
            // cerr << "i = " << i << ", j = " << j << " dp = " << res + 1 << endl;
            put(r, res + 1, j);
        }
    }

    int ans = n;
    int x = get_max(0, n).second;
    vector<int> on_stack(n+1, 0);
    while (x != 0) {
        // cerr << x << endl;
        on_stack[x] = 1;
        ans--;
        int last = from[x];
        int between = a[x] - a[last] - 1;
        for (int i = 1; i <= between; i++) {
            on_stack[last+i] = 1;
            ans--;
        } 

        x = last;
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++) {
        if (!on_stack[i]) {
            cout << i << " ";
        }
    }

    cout << "\n";
}