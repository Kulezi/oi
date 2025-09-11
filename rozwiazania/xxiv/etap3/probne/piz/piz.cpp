// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MAXN = 100'005;

vector<pair<int, int>> g[MAXN];
int par[MAXN], weight[MAXN];
int pre[MAXN], post[MAXN], leaf[MAXN], rev[MAXN];
ll gain[MAXN], lazy[4 * MAXN];

vector<int> ord;

int T;
void dfs(int v) {
    pre[v] = ++T;
    rev[T] = v;

    for (auto &[u, w] : g[v]) {
        if (u != par[v]) {
            par[u] = v;
            weight[u] = w;
            gain[u] = gain[v] + w;
            dfs(u);
        }
    }

    post[v] = T;
}

// Pozycja maxa, max.
pair<ll, int> tree[MAXN * 4];
void build(int pos, int l, int r) {
    if (l == r) {
        if (l == 1 || g[l].size() != 1) tree[pos] = {-1, rev[l]};
        tree[pos] = {gain[rev[l]], rev[l]};
        return;
    }

    int m = (l + r) / 2;
    build(pos * 2, l, m);
    build(pos * 2 + 1, m + 1, r);
    tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
}

void add(int ql, int qr, ll delta, int pos, int l, int r) {
    if (lazy[pos]) {
        tree[pos].first += lazy[pos];
        if (l != r) {
            lazy[pos * 2] += lazy[pos];
            lazy[pos * 2 + 1] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        tree[pos].first += delta;
        if (l != r) {
            lazy[pos * 2] += delta;
            lazy[pos * 2 + 1] += delta;
        }
        return;
    }

    int m = (l + r) / 2;
    add(ql, qr, delta, pos*2, l, m);
    add(ql, qr, delta, pos*2+1, m+1, r);
    tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;

    long long ans = 0;
    for (int i = 2; i <= n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        ans += 2 * w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    par[1] = -1;
    dfs(1);

    build(1, 1, n);

    while (k--) {
        auto [best_gain, best] = tree[1];
        if (best_gain <= 0) break;
        ans -= best_gain;
 
        while (best != 1 && weight[best] > 0) {
            add(pre[best], post[best], -2 * weight[best], 1, 1, n);
            weight[best] = -weight[best];
            best = par[best];
        }
    }

    cout << ans << "\n";
}