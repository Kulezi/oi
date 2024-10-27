// Rozwiązanie wolne do zadania 'Pustynia' z II etapu XXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * log(n))
// Złożoność pamięciowa: O(n * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 200005 * 5;
int glebokosc[MAXN], oryginal[MAXN], out[MAXN], id[MAXN];
vector<int> grev[MAXN];
int n, s, m;
void add_edge(int src, int dst) {
    out[src]++;
    grev[dst].push_back(src);
}

int mx;

void build(int pos, int l, int r) {
    if (l == r) {
        if (pos > 1) add_edge(pos / 2 + n + m, l);
        return;
    }

    mx = max(mx, pos + n + m);
    if (pos > 1) add_edge(pos / 2 + n + m, pos + n + m);
    int m = (l + r) / 2;
    build(pos * 2, l, m);
    build(pos * 2 + 1, m + 1, r);
}

void add_edges(int pos, int l, int r, int src, int ql, int qr) {
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        if (l != r)
            add_edge(src, pos + n + m);
        else
            add_edge(src, l);
        return;
    }

    int m = (l + r) / 2;
    add_edges(pos * 2, l, m, src, ql, qr);
    add_edges(pos * 2 + 1, m + 1, r, src, ql, qr);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> s >> m;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        glebokosc[i] = 1;
    }

    while (s--) {
        int p, d;
        cin >> p >> d;
        glebokosc[p] = d;
        oryginal[p] = d;
    }

    for (int q = 1; q <= m; q++) {
        int l, r, k;
        cin >> l >> r >> k;

        int lo = l;

        int query_vertex = n + q;

        while (k--) {
            int x;
            cin >> x;
            add_edge(x, query_vertex);

            int hi = x - 1;
            if (x - 1 >= lo) add_edges(1, 1, n, query_vertex, lo, hi);

            lo = x + 1;
        }

        if (lo <= r) add_edges(1, 1, n, query_vertex, lo, r);
    }

    queue<int> q;
    for (int i = 1; i <= mx; i++) {
        if (!out[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : grev[u]) {
            glebokosc[v] = max(glebokosc[v], glebokosc[u] + (u >= 1 && u <= n));
            out[v]--;
            if (!out[v]) q.push(v);
        }
    }

    for (int u = 1; u <= n; u++) {
        if (out[u] || glebokosc[u] > 1'000'000'000 ||
            (oryginal[u] && glebokosc[u] != oryginal[u])) {
            cout << "NIE\n";
            return 0;
        }
        for (auto v : grev[u]) {
            if (glebokosc[u] >= glebokosc[v]) {
                cout << "NIE\n";
                return 0;
            }
        }
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; i++) {
        cout << glebokosc[i] << " ";
    }

    cout << "\n";
}