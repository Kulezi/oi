// Rozwiązanie do zadania 'Meteory'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n + m)^2 * log(m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 27 (upsolve)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using ll = long long;

struct Tree {
    int n;
    vector<ll> v;
    Tree(int N) : n(N), v(N + 1, 0) {}

    void add(int l, int r, int delta) {
        if (l > r) {
            add(1, r, delta);
            add(l, n, delta);
            return;
        }

        for (int i = l; i <= r; i++) v[i] += delta;
    }

    ll query(int x) { return v[x]; }

    void print() {
        // for (int i = 1; i <= n; i++) cerr << v[i] << " ";
        // cerr << "\n";
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    vector stations(n + 1, vector<int>());
    for (int i = 1; i <= m; i++) {
        int owner;
        cin >> owner;
        stations[owner].push_back(i);
    }

    vector<int> need(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> need[i];
    }

    int k;
    cin >> k;
    vector<int> l(k + 1), r(k + 1), delta(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> l[i] >> r[i] >> delta[i];
    }

    priority_queue<tuple<int, int, int, int>> q, nq;
    for (int i = 1; i <= n; i++) {
        int lo = 1, hi = k + 1;
        q.push({-(lo + hi) / 2, i, lo, hi});
    }

    vector<int> ans(n + 1);
    while (!q.empty()) {
        int i = 0;
        Tree tree(m);
        while (!q.empty()) {
            auto [mid, country, lo, hi] = q.top();
            mid *= -1;
            q.pop();
            if (lo == hi) {
                ans[country] = mid;
            } else {
                while (i < k && i < mid) {
                    i++;
                    tree.add(l[i], r[i], delta[i]);
                }

                assert(i == mid || i == k);
                tree.print();

                ll sum = 0;
                for (auto station : stations[country]) {
                    sum += tree.query(station);
                }

                if (sum >= need[country]) {
                    nq.push({-(lo + mid) / 2, country, lo, mid});
                } else {
                    q.push({-(mid + 1 + hi) / 2, country, mid + 1, hi});
                }
            }
        }

        swap(q, nq);
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == k + 1)
            cout << "NIE\n";
        else
            cout << ans[i] << "\n";
    }
}