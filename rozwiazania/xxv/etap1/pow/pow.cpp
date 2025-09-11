// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(nm*log(n*m))
// Punkty: 100

// Rozwiązanie oparte na łączeniu obszarów w kolejności rosnących wysokości.
// DSU https://en.wikipedia.org/wiki/Disjoint-set_data_structure
#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
using namespace std;
int r[1000005], RANK[1000005], res, m, n, h, hres, M = 1e9 + 7, ra, rb;
long long t[1 << 19], H[1 << 19], x;
vector<pair<int, pair<int, int> > > v;
int Find(int a) {
    if (r[a] != a) r[a] = Find(r[a]);
    return r[a];
}
inline void fi(long long &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
main() {
    cin >> m >> n >> h;
    h++;
    for (int i = 1; i <= m * n; i++) r[i] = i, t[i] = INT_MAX;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j < n; j++) {
            fi(x);
            t[(i - 1) * n + j] = min(t[(i - 1) * n + j], x + 1);
            t[(i - 1) * n + j + 1] = min(t[(i - 1) * n + j + 1], x + 1);
            v.push_back({x + 1, {(i - 1) * n + j, (i - 1) * n + j + 1}});
        }
    for (int i = 1; i < m; i++)
        for (int j = 1; j <= n; j++) {
            fi(x);
            t[(i - 1) * n + j] = min(t[(i - 1) * n + j], x + 1);
            t[i * n + j] = min(t[i * n + j], x + 1);
            v.push_back({x + 1, {(i - 1) * n + j, i * n + j}});
        }
    for (int i = 1; i <= m * n; i++) H[i] = t[i];
    sort(v.begin(), v.end());
    for (auto i : v) {
        ra = Find(i.s.f), rb = Find(i.s.s);
        if (ra != rb) {
            if (RANK[ra] >= RANK[rb]) {
                if (RANK[ra] == RANK[rb]) RANK[ra]++;
                t[ra] = (t[ra] + (ll)i.f - H[ra]) * (t[rb] + (ll)i.f - H[rb]);
                t[ra] %= M;
                res = t[ra];
                hres = i.f;
                H[ra] = i.f;
                r[rb] = ra;
            } else if (RANK[rb] > RANK[ra]) {
                t[rb] = (t[ra] + i.f - H[ra]) * (t[rb] + i.f - H[rb]);
                t[rb] %= M;
                res = t[rb];
                hres = i.f;
                H[rb] = i.f;
                r[ra] = rb;
            }
        }
    }
    res += h - hres;
    res %= M;
    cout << res;
}