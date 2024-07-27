// Rozwiązanie do zadania 'Kolacje' z II etapu XXVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * sqrt(n) * log(n)).
// Punkty: 80 (100 na szkopule)

// HLD + SQRT decomposition.
// int t[M], dist[M], pre[M], sub[M], post[M], par[M], head[M], dep[M], A[M], B[M], W[M], ord[M],
// ans[M], used[M], tree[4 * M], DIST[M], rev[M], zap[M]; XD ILE TABLIC grupy++-???-
#define M 100005
const int SZ = 310;
#define ff first
#define ss second
#define ll long long
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, r, a, b, w, q, czas, ql, qp;
int t[M], dist[M], pre[M], sub[M], post[M], par[M], head[M], dep[M], A[M], B[M], W[M], ord[M],
    ans[M], used[M], tree[4 * M], DIST[M], rev[M], zap[M];
vector<pair<int, int> > g[M];
vector<int> V[M];
priority_queue<pair<ll, int> > pq;
void subs(int v) {
    sub[v] = 1;
    for (auto &u : g[v]) {
        if (!sub[u.ff]) {
            par[u.ff] = v;
            subs(u.ff);
            sub[v] += sub[u.ff];
        }
        if (sub[u.ff] > sub[g[v][0].ff] || g[v][0].ff == par[v]) swap(u, g[v][0]);
    }
}
void hld(int v) {
    pre[v] = ++czas;
    rev[czas] = v;
    for (auto u : g[v]) {
        if (!pre[u.ff]) {
            if (u.ff == g[v][0].ff)
                head[u.ff] = head[v];
            else
                head[u.ff] = u.ff;
            dist[u.ff] = dist[v] + u.ss;
            dep[u.ff] = dep[v] + 1;
            hld(u.ff);
        }
    }
    post[v] = czas;
}
int lca(int a, int b) {
    while (head[a] != head[b]) {
        if (dep[head[a]] < dep[head[b]]) swap(a, b);
        a = par[head[a]];
    }
    if (dep[a] <= dep[b]) return a;
    return b;
}
int getdist(int a, int b) {
    int LCA = lca(a, b);
    return dist[a] + dist[b] - 2LL * dist[LCA];
}
bool comp(int a, int b) { return W[a] < W[b]; }
void build(int pos = 1, int l = 1, int p = n) {
    if (l == p) {
        tree[pos] = DIST[rev[l]];
        return;
    }
    int mid = (l + p) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, p);
    tree[pos] = min(tree[pos << 1], tree[pos << 1 | 1]);
}
ll query(int pos = 1, int l = 1,
         int p = n) {  // cout << pos << " " << l << " " << p << " " << ql << " " << qp << endl;
    if (l > qp || p < ql) return LLONG_MAX;
    if (l >= ql && p <= qp) return tree[pos];
    int mid = (l + p) >> 1;
    return min(query(pos << 1, l, mid), query(pos << 1 | 1, mid + 1, p));
}
ll policz(int cur, int dest) {
    ll res = DIST[cur];
    while (head[cur] != head[dest]) {
        ql = pre[head[cur]];
        qp = pre[cur];
        // cout << ql << " " << qp << "\n";
        res = min(res, query());
        // cout << query() << endl;
        cur = par[head[cur]];
    }
    ql = pre[dest];
    qp = pre[cur];
    // cout << ql << " " << qp << "\n";
    res = min(res, query());
    // cout << query() << endl;
    return res;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> r;
    par[1] = dep[1] = head[1] = 1;
    for (int i = 1; i <= n; i++) cin >> t[i], V[t[i]].push_back(i);
    for (int i = 1; i < n; i++) cin >> a >> b >> w, g[a].push_back({b, w}), g[b].push_back({a, w});

    subs(1);
    hld(1);
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> A[i] >> B[i] >> W[i], ord[i] = i;
    sort(ord + 1, ord + q + 1, comp);
    for (int kek = 1; kek <= q; kek++) {
        int last = ord[kek - 1];
        int i = ord[kek];
        if (V[W[i]].empty()) {
            ans[i] = -1;
        } else if (V[W[i]].size() <= SZ) {
            ans[i] = LLONG_MAX;
            for (auto c : V[W[i]]) ans[i] = min(ans[i], getdist(A[i], c) + getdist(B[i], c));
        } else {
            if (W[last] != W[i]) {
                for (int j = 1; j <= n; j++) DIST[j] = LLONG_MAX, used[j] = 0;
                for (auto c : V[W[i]]) {
                    DIST[c] = 0;
                    pq.push({0, c});
                }
                while (!pq.empty()) {
                    int v = pq.top().second;
                    pq.pop();
                    if (used[v]) continue;
                    used[v] = 1;
                    for (auto u : g[v]) {
                        if (DIST[v] + u.ss <
                            DIST[u.ff]) {  // cout << "v - > u " << v << " " << u.first << endl;
                            DIST[u.ff] = DIST[v] + u.ss;
                            pq.push({-DIST[u.ff], u.ff});
                        }
                    }
                }
                // cout << pre[7] << " " << rev[7] << endl;
                // for(int j = 1; j <= n; j++)
                //  cout << DIST[rev[j]] << " ";
                // zap[j] = DIST[rev[j]], cout << zap[j] << " " << pre[j] << " " << rev[pre[j]] <<
                // endl;
                build();
            }
            int LCA = lca(A[i], B[i]);
            // cout << min(policz(A[i], LCA), policz(B[i], LCA)) << "\n";
            ans[i] = 2LL * min(policz(A[i], LCA), policz(B[i], LCA)) + getdist(A[i], B[i]);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
}