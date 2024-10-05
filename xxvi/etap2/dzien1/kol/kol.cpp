// Rozwiązanie do zadania 'Kolacje' z II etapu XXVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
constexpr ll INF = 1e18;

struct Tree {
    int n, LOG;
    vector<vector<pil>> g;
    vector<int> pre, post;
    vector<ll> dis;
    vector<vector<int>> par;
    Tree(int _n)
        : n(_n),
          LOG(__lg(n) + 1),
          g(n, vector<pil>()),
          pre(n),
          post(n),
          dis(n, 0),
          par(n + 1, vector<int>(LOG + 1)) {}

    void add_edge(int a, int b, ll w) {
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }

    int T = 0;
    void root(int v, int p) {
        pre[v] = ++T;
        par[v][0] = p;
        for (int i = 1; i <= LOG; i++) par[v][i] = par[par[v][i - 1]][i - 1];
        for (auto [u, w] : g[v]) {
            if (u == p) continue;
            dis[u] = dis[v] + w;
            root(u, v);
        }
        post[v] = T;
    }

    bool is_parent(int parent, int child) {
        return pre[parent] <= pre[child] && post[parent] >= pre[child];
    }

    int lca(int a, int b) {
        if (is_parent(a, b)) return a;
        for (int i = LOG; i >= 0; i--)
            if (!is_parent(par[a][i], b)) a = par[a][i];
        return par[a][0];
    }

    ll dist(int a, int b) { return dis[a] + dis[b] - 2 * dis[lca(a, b)]; }

    map<int, int> id;
    Tree contracted_subtree(vector<int> &s) {
        sort(all(s), [&](int a, int b) { return pre[a] < pre[b]; });
        s.erase(unique(all(s)), s.end());

        for (int i = (int)s.size() - 2; i >= 0; i--) {
            int a = s[i];
            int b = s[i + 1];
            s.push_back(lca(a, b));
        }

        sort(all(s), [&](int a, int b) { return pre[a] < pre[b]; });
        s.erase(unique(all(s)), s.end());

        int N = 0;
        map<int, int> scale;
        for (auto i : s) scale[i] = N++;

        Tree g_compressed(N);
        g_compressed.id = scale;
        vector<int> path = {1};
        for (int i = 1; i < N; i++) {
            while (!is_parent(path.back(), s[i])) path.pop_back();
            int j = scale[path.back()];
            ll w = dist(path.back(), s[i]);
            path.push_back(s[i]);
            g_compressed.add_edge(i, j, w);
        }

        g_compressed.root(0, 0);
        return g_compressed;
    }

    vector<ll> closest;
    vector<vector<ll>> closest_jmp;
    void run_dijkstra(vector<int> verts) {
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        closest = vector(n, INF);
        closest_jmp = vector(n, vector<ll>(LOG + 1, INF));
        for (auto i : verts) {
            int v = id[i];
            closest[v] = 0;
            pq.push({0, v});
        }

        vector<bool> used(n, false);
        while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (used[v]) continue;
            used[v] = true;
            for (auto [u, w] : g[v]) {
                if (closest[u] > d + w) {
                    closest[u] = d + w;
                    pq.push({closest[u], u});
                }
            }
        }

        for (int i = 0; i < n; i++) closest_jmp[i][0] = min(closest[i], closest[par[i][0]]);
        for (int j = 1; j <= LOG; j++) {
            for (int i = 0; i < n; i++) {
                int ojciec = par[i][j-1];
                closest_jmp[i][j] = min(closest_jmp[i][j-1], closest_jmp[ojciec][j-1]);
            }
        }
    }

    ll closest_on_path(int u, int v) {
        u = id[u], v = id[v];
        int l = lca(u, v);
        ll res = min({closest[u], closest[v], closest[l]});
        for (int i = LOG; i >= 0; i--) {
            if (!is_parent(par[u][i], l)) res = min(res, closest_jmp[u][i]), u = par[u][i];
            if (!is_parent(par[v][i], l)) res = min(res, closest_jmp[v][i]), v = par[v][i];
        }
        return res;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, r;
    cin >> n >> r;

    vector<int> t(n + 1);
    vector special(r + 1, vector<int>{1}), restaurants(r + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        special[t[i]].push_back(i);
        restaurants[t[i]].push_back(i);
    }

    Tree g(n + 1);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.add_edge(a, b, c);
    }

    g.root(1, 1);

    int z;
    cin >> z;
    vector<ll> ans(z);
    // Zapytania (poczatek, koniec )
    vector queries(r + 1, vector<tuple<int, int, int>>());
    for (int i = 0; i < z; i++) {
        int p, q, s;
        cin >> p >> q >> s;
        special[s].push_back(p);
        special[s].push_back(q);
        queries[s].emplace_back(p, q, i);
        ans[i] = g.dist(p, q);
    }

    for (int color = 1; color <= r; color++) {
        Tree g_compressed = g.contracted_subtree(special[color]);
        g_compressed.run_dijkstra(restaurants[color]);
        for (auto &[p, q, i] : queries[color]) {
            ans[i] += 2LL * g_compressed.closest_on_path(p, q);
        }
    }

    for (auto i : ans) {
        cout << (i < INF ? i : -1) << "\n";
    }
}

// dist(a, c) + dist(b, c) = dist(a, lca(a, b)) + dist(b, lca(a, b)) + 2 * dist(lca(a, b), c)