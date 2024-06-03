// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * sqrt(n) * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int THRESHOLD = 500, MAXN = 100005, MAXM = 150005, TREE_B = (1 << 19);
char c;
int n, m, z, MAX_TIME, a, b;
int A[MAXN], B[MAXN], W[MAXN], lac[MAXN], cnt[MAXM];
int seg[TREE_B * 2], in[MAXN], out[MAXN], head[MAXN], sub[MAXN], par[MAXN];
set<pii> nodes_on_chain[MAXN];
set<int> special_colors, nodes_of_color[MAXM];
vector<int> g[MAXN];
vector<vector<int>> zap;
void order_subtrees(int v) {
    sub[v] = 1;
    for (int &u : g[v]) {
        if (!sub[u]) {
            par[u] = v;
            order_subtrees(u);
            sub[v] += sub[u];
        }

        if (sub[u] > sub[g[v][0]] || g[v][0] == par[v]) swap(u, g[v][0]);
    }
}
void hld(int v, int cur_chain) {
    in[v] = ++MAX_TIME;
    head[v] = cur_chain;
    for (const int &u : g[v]) {
        if (!in[u]) {
            hld(u, (u == g[v][0] ? cur_chain : u));
        }
    }

    out[v] = MAX_TIME;
}
bool is_parent(int v, int u) { return (in[v] <= in[u] && out[v] >= out[u]); }
void seg_add(int pos, int x) {
    // if(pos >= 71 && pos <= 74) cout << pos << " " << x << endl;
    pos += TREE_B;
    while (pos > 0) {
        seg[pos] += x;
        pos >>= 1;
    }
}
int seg_query(int l, int r) {
    // cout << "(" << l << ", " << r << ") -> ";
    int res = 0;
    l += TREE_B, r += TREE_B;
    while (l > 1) {
        if (l % 2 == 1) res += seg[l - 1];
        l >>= 1;
    }
    while (r > 1) {
        if (r % 2 == 0) res += seg[r + 1];
        r >>= 1;
    }

    // cout << seg[1] - res << "\n";
    return seg[1] - res;
}
void insert_node(int v, int color) {
    nodes_on_chain[head[v]].insert({color, in[v]});
    if (!special_colors.count(color)) {
        int best_idx = 0;
        for (auto u : nodes_of_color[color]) {
            if (is_parent(v, u) && is_parent(lac[u], v)) {
                if (!lac[u]) seg_add(in[u], -1);
                lac[u] = v;
            }

            if (is_parent(u, v) && is_parent(best_idx, u)) best_idx = u;
        }

        lac[v] = best_idx;
        if (!lac[v]) seg_add(in[v], 1);
    }

    nodes_of_color[color].insert(v);
}
void erase_node(int v, int color) {
    nodes_on_chain[head[v]].erase({color, in[v]});
    if (!special_colors.count(color)) {
        int best_idx = 0;
        for (auto u : nodes_of_color[color]) {
            if (lac[u] == v) {
                if (!lac[v]) seg_add(in[u], 1);
                lac[u] = lac[v];
            }

            if (is_parent(u, v) && in[best_idx] < in[u]) best_idx = u;
        }

        if (!lac[v]) seg_add(in[v], -1);
    }

    nodes_of_color[color].erase(v);
}
void preprocess() {
    for (int i = 1; i < n; i++) cnt[W[i]]++;

    for (auto i : zap)
        if (i.size() == 2) cnt[i[1]]++;

    for (int i = 1; i <= m; i++) {
        if (cnt[i] >= THRESHOLD) special_colors.insert(i);
    }

    out[0] = MAXN;
    order_subtrees(1);
    hld(1, 1);
    for (int i = 1; i < n; i++) {
        if (in[A[i]] > in[B[i]]) swap(A[i], B[i]);
        // if(special_colors.count(W[i]))
        ///	seg_add(B[i], -1);
    }

    for (int i = 1; i < n; i++) {
        insert_node(B[i], W[i]);
    }
}
int is_on_path(int v, int color) {
    while (v > 1) {
        auto it = nodes_on_chain[head[v]].lower_bound({color, 0});
        if (it != nodes_on_chain[head[v]].end() && (*it).first == color && (*it).second <= in[v]) {
            return 1;
        }

        v = par[head[v]];
    }

    return 0;
}

int query(int x) {
    int res = 0;
    for (auto &i : special_colors) {
        res += is_on_path(x, i);
    }
    // cout << res << "\n";
    while (x > 1) {
        res += seg_query(in[head[x]], in[x]);
        // cout << in[head[x]] <<  " " << in[x] << " " << res << "\n";
        x = par[head[x]];
    }

    return res;
}
void modify(int x, int y) {
    erase_node(B[x], W[x]);
    W[x] = y;
    insert_node(B[x], W[x]);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> z;
    for (int i = 1; i < n; i++) {
        cin >> A[i] >> B[i] >> W[i];
        g[A[i]].push_back(B[i]);
        g[B[i]].push_back(A[i]);
    }
    for (int i = 1; i <= z; i++) {
        cin >> c;
        if (c == 'Z') {
            cin >> a;
            zap.push_back({a});
        } else {
            cin >> a >> b;
            zap.push_back({a, b});
        }
    }
    preprocess();
    for (auto i : zap) {
        if (i.size() == 1) {
            cout << query(i[0]) << "\n";
        } else {
            modify(i[0], i[1]);
        }
    }
    return 0;
}