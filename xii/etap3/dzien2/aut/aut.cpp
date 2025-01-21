// Rozwiązanie do zadania 'Autobus' z III etapu XII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(k * log(n))
// Złożoność pamięciowa: O(k * log(n))
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 100'005;
int x[MAXN], y[MAXN], p[MAXN], ord[MAXN];

struct Tree {
    Tree *left, *right;
    int lo, hi;
    int max;

    int query(int l, int r) {
        if (l > hi || r < lo) return 0;
        if (lo >= l && hi <= r) {
            return max;
        }
        int m = (lo + hi) / 2;

        return std::max((!left ? 0 : left->query(l, r)), (!right ? 0 : right->query(l, r)));
    };

    void insert(int x, int val) {
        if (x < lo || x > hi) return;
        if (x == lo && x == hi) {
            max = val;
            return;
        }
        int m = (lo + hi) / 2;
        if (x <= m) {
            if (left == nullptr) left = new Tree{NULL, NULL, lo, m, 0};
            left->insert(x, val);
            max = std::max(max, left->max);
        } else {
            if (right == nullptr) right = new Tree{NULL, NULL, m + 1, hi, 0};
            right->insert(x, val);
            max = std::max(max, right->max);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        cin >> x[i] >> y[i] >> p[i];
        ord[i] = i;
    }

    sort(ord, ord + k, [&](int a, int b) {
        if (x[a] == x[b]) return y[a] < y[b];
        return x[a] < x[b];
    });

    Tree tree{NULL, NULL, 1, n, 0};
    for (int w = 0; w < k; w++) {
        int i = ord[w];
        int ile = tree.query(1, y[i]) + p[i];
        tree.insert(y[i], ile);
    }

    cout << tree.query(1, n) << "\n";
}