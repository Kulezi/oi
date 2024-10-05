// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((m_1+m_2)*log(m_1+m_2)
// Punkty: 100 (upsolve)

// Interpretuje zadanie jako prostokąty na płaszczyźnie i rozwiązuję zamiataniem z drzewem
// przedziałowym. Wymyślone przy kawie w kawiarni Combi Coffee Roasters, Porto 2021.
#include <bits/stdc++.h>
using namespace std;
const int MAX_SEGS = 1000, MAX_RECT = 2 * 1005 * 1005, B = 300;
const int INF = 2e9;
int full[4 * MAX_RECT][2], t[MAX_RECT][2], last[4 * MAX_RECT][3];
struct event_t {
    int x, min_y, max_y, delta, dim;
};

bool compare(const event_t &lhs, const event_t &rhs) {
    if (lhs.x == rhs.x) {
        return lhs.delta > rhs.delta;
    }

    return lhs.x < rhs.x;
}

int n[3], a[2][MAX_SEGS + 5], res, N;
map<int, int> scale;
int rev[MAX_RECT];
char c;

vector<event_t> events;

void create_rectangle(int min_x, int max_x, int min_y, int max_y, int dim) {
    scale[min_y] = 1;
    scale[max_y] = 1;
    events.push_back({min_x, min_y, max_y, 1, dim});
    events.push_back({max_x, min_y, max_y, -1, dim});
}

int query() { return (last[1][2] == -INF ? N + 1 : last[1][2]); }

void get_rectangles() {
    for (int dim = 0; dim < 2; ++dim) {
        cin >> n[dim];

        for (int i = 1; i <= n[dim]; ++i) {
            cin >> c >> a[dim][i];
            if (c == 'W') {
                a[dim][i] *= -1;
            }
        }

        for (int i = 1; i <= n[dim]; ++i) {
            int min_x = 0, min_y = 0;

            if (a[dim][i] > 0) {
                create_rectangle(0, a[dim][i], 0, -a[dim][i - 1], dim);
            } else {
                create_rectangle(0, a[dim][i - 1], 0, -a[dim][i], dim);
            }

            for (int j = i; j <= n[dim]; ++j) {
                if (a[dim][j] > 0) {
                    min_x += a[dim][j];
                } else {
                    min_y -= a[dim][j];
                }

                int max_x = min_x, max_y = min_y;
                if (a[dim][i] > 0) {
                    max_y -= a[dim][i - 1];
                } else {
                    max_x += a[dim][i - 1];
                }

                if (a[dim][j] > 0) {
                    max_y -= a[dim][j + 1];
                } else {
                    max_x += a[dim][j + 1];
                }

                create_rectangle(min_x, max_x, min_y, max_y, dim);
            }
        }
    }
}

void build(int pos, int l, int r) {
    for (int i = 0; i < 3; ++i) {
        last[pos][i] = -INF;
    }

    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
}

void merge(int pos, int l, int r) {
    for (int i = 0; i < 3; ++i) {
        last[pos][i] = max(last[pos << 1][i], last[pos << 1 | 1][i]);
    }

    if (full[pos][0] && full[pos][1]) {
        last[pos][2] = last[pos][1] = last[pos][0] = r;
    } else if (full[pos][0]) {
        last[pos][2] = last[pos][1];
        last[pos][0] = r;
    } else if (full[pos][1]) {
        last[pos][2] = last[pos][0];
        last[pos][1] = r;
    }
}

void add(int pos, int l, int r, int ql, int qr, int dim) {
    if (r < ql || l > qr) {
        return;
    }

    if (l >= ql && r <= qr) {
        ++full[pos][dim];

        if (l != r) {
            merge(pos, l, r);
        } else {
            last[pos][0] = (full[pos][0] ? r : -INF);
            last[pos][1] = (full[pos][1] ? r : -INF);
            if (full[pos][0] && full[pos][1]) {
                last[pos][2] = r;
            } else {
                last[pos][2] = -INF;
            }
        }

        return;
    }

    int mid = (l + r) >> 1;
    add(pos << 1, l, mid, ql, qr, dim);
    add(pos << 1 | 1, mid + 1, r, ql, qr, dim);
    merge(pos, l, r);
}

void sub(int pos, int l, int r, int ql, int qr, int dim) {
    if (r < ql || l > qr) {
        return;
    }

    if (l >= ql && r <= qr) {
        --full[pos][dim];
        if (l != r) {
            merge(pos, l, r);
        } else {
            last[pos][0] = (full[pos][0] ? r : -INF);
            last[pos][1] = (full[pos][1] ? r : -INF);
            if (full[pos][0] && full[pos][1]) {
                last[pos][2] = r;
            } else {
                last[pos][2] = -INF;
            }
        }

        return;
    }

    int mid = (l + r) >> 1;
    sub(pos << 1, l, mid, ql, qr, dim);
    sub(pos << 1 | 1, mid + 1, r, ql, qr, dim);

    merge(pos, l, r);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    get_rectangles();

    sort(events.begin(), events.end(), compare);
    for (auto &i : scale) {
        rev[++N] = i.first;
        i.second = N;
    }

    build(1, 1, N);
    rev[N + 1] = -2e9;
    for (auto &i : events) {
        res = max(res, i.x + rev[query()]);

        i.min_y = scale[i.min_y];
        i.max_y = scale[i.max_y];
        if (i.delta > 0) {
            add(1, 1, N, i.min_y, i.max_y, i.dim);
        } else {
            sub(1, 1, N, i.min_y, i.max_y, i.dim);
        }
    }

    cout << res;
}