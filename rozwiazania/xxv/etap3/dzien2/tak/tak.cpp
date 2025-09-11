// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n+q*log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define pr pair<rational, rational>
using namespace std;
struct rational {
    int p, q;

    void print() { cout << p << "/" << q << "\n"; }
};

const rational MIN = {1, (int)1e9}, MAX = {(int)1e9, 1};
const pr FULL = {MIN, MAX}, EMPTY = {MAX, MIN};
const int MX = 500005;

int n, q, a[MX], b[MX], ord[MX];
pr range[4 * MX];

bool compare(rational a, rational b) { return 1LL * a.p * b.q < 1LL * b.p * a.q; }

rational normalize(int a, int b) {
    if (a == 0) return {a, abs(b)};

    if (b < 0) {
        a = -a;
        b = -b;
    }

    int g = abs(__gcd(a, b));
    return {a / g, b / g};
}

pr get_range(int l, int r) {
    if (b[l] - b[r] == 0 && a[l] <= a[r]) {
        return FULL;
    } else if (b[l] - b[r] == 0) {
        return EMPTY;
    } else {
        rational intersection = normalize(a[r] - a[l], b[l] - b[r]);
        if (b[l] - b[r] > 0) {
            return {MIN, intersection};
        } else {
            return {intersection, MAX};
        }
    }
}

pr merge(pr a, pr b) {
    pr res;
    if (compare(a.first, b.first)) {
        res.first = b.first;
    } else {
        res.first = a.first;
    }

    if (compare(a.second, b.second)) {
        res.second = a.second;
    } else {
        res.second = b.second;
    }

    return res;
}

void query() {
    if (compare(range[1].second, range[1].first)) {
        cout << "NIE\n";
    } else {
        range[1].first.print();
    }
}

void build(int pos, int l, int r) {
    if (l == r) {
        range[pos] = FULL;
        return;
    }

    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
    pr connector = get_range(ord[mid], ord[mid + 1]);
    range[pos] = merge(range[pos << 1], range[pos << 1 | 1]);
    range[pos] = merge(range[pos], connector);
}

void update(int pos, int l, int r, int x) {
    if (r < x || l > x || l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    update(pos << 1, l, mid, x);
    update(pos << 1 | 1, mid + 1, r, x);
    pr connector = get_range(ord[mid], ord[mid + 1]);
    range[pos] = merge(range[pos << 1], range[pos << 1 | 1]);
    range[pos] = merge(range[pos], connector);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> ord[i];
    }

    build(1, 1, n);
    query();

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        swap(ord[x], ord[y]);
        update(1, 1, n, x);
        update(1, 1, n, y);

        query();
    }
}