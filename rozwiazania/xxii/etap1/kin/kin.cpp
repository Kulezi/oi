// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#ifdef _WIN32
#define getchar_unlocked getchar
#endif
inline void fin(int &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}

using namespace std;
using ll = long long;
int n, m, t[1 << 20], ql, qp, val, w[1 << 20];
ll lazy[1 << 22], tree[1 << 22], res;
vector<int> v[1 << 20];
inline void lazify(int pos, int l, int p) {
    if (lazy[pos]) {
        tree[pos] += lazy[pos];
        if (l != p)
            lazy[pos << 1] += lazy[pos], lazy[pos << 1 | 1] += lazy[pos];
        lazy[pos] = 0;
    }
}
inline void insert(int pos = 1, int l = 1, int p = n) {
    lazify(pos, l, p);
    if (l > qp || p < ql) return;
    if (ql <= l && qp >= p) {
        tree[pos] += val;
        if (l != p) {
            lazy[pos << 1] += val;
            lazy[pos << 1 | 1] += val;
        }
        return;
    }
    int mid = (l + p) >> 1;
    insert(pos << 1, l, mid);
    insert(pos << 1 | 1, mid + 1, p);
    tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
}
int main() {
    fin(n);
    fin(m);
    for (int i = 1; i <= n; i++) {
        fin(t[i]);
        v[t[i]].push_back(i);
    }
    for (int i = 1; i <= m; i++) fin(w[i]);
    for (int i = 1; i <= m; i++) {
        if (v[i].empty()) continue;
        if (v[i].size() == 1) {
            ql = 1, qp = v[i].back(), val = w[i];
            insert();
        } else {
            qp = v[i].back(), ql = v[i][v[i].size() - 2] + 1, val = w[i];
            insert();
        }
    }
    res = tree[1];
    for (int j = n; j >= 1; j--) {
        int i = t[j];
        val = -w[i];
        if (v[i].empty()) continue;
        if (v[i].size() == 1)
            ql = 1, qp = v[i].back();
        else
            qp = v[i].back(), ql = v[i][v[i].size() - 2] + 1;
        insert();
        v[i].pop_back();
        val = w[i];
        if (v[i].empty()) continue;
        if (v[i].size() == 1)
            ql = 1, qp = v[i].back();
        else
            qp = v[i].back(), ql = v[i][v[i].size() - 2] + 1;
        insert();
        res = max(res, tree[1]);
    }
    cout << res << "\n";
}