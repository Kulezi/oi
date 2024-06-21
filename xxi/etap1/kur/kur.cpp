// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAXN = 500005, REPS = 40;

vector<int> v[MAXN];
int t[MAXN];
int main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) v[i].push_back(0);
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        v[t[i]].push_back(i);
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        int res = 0;
        for (int rep = 0; rep < REPS; rep++) {
            int x = t[R(a, b)];
            int l = 0;
            int p = v[x].size() - 1;
            int kon = (l + p + 1) / 2;
            while (l != p) {
                if (v[x][kon] > b)
                    p = kon - 1;
                else
                    l = kon;
                kon = (l + p + 1) / 2;
            }
            if (kon == 0) continue;

            l = 0;
            p = kon;
            int pocz = (l + p) / 2;
            while (l != p) {
                if (v[x][pocz] < a)
                    l = pocz + 1;
                else
                    p = pocz;
                pocz = (l + p) / 2;
            }
            if (kon - pocz + 1 > (b - a + 1) / 2) {
                res = x;
                break;
            }
        }
        cout << res << "\n";
    }
}