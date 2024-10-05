// Rozwiązanie do zadania 'Magazynier' z III etapu VI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m * log(n * m))
// Złożoność pamięciowa: O(n * m * log(n * m))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100, MAX_NODES = MAXN * MAXN;
string s[MAXN];
int n, m;
bool bad(int x, int y) { return x < 0 || x >= n || y < 0 || y >= m || s[x][y] == 'S'; }
int id(int x, int y) { return x * MAXN + y; }

enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};
int inv(int dir) { return dir ^ 1; }
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int E;
vector<tuple<int, int, int>> g[MAX_NODES];
vector<tuple<int, int>> edges = {{}};
int e[MAXN][MAXN][4];

int m_x, m_y, p_x, p_y, k_x, k_y;
int vis[MAX_NODES];
int dfs_dir(int src, int dst) {
    vis[src] = 1;
    for (auto [v, dir, e] : g[src]) {
        if (v == dst) return dir;
        if (!vis[v]) {
            int d = dfs_dir(v, dst);
            if (d != -1) return d;
        }
    }

    return -1;
}

int in[MAX_NODES], out[MAX_NODES], low[MAX_NODES], par[MAX_NODES];

int dfs_low(int v, int p) {
    static int T = 0;
    low[v] = in[v] = ++T;
    par[v] = p;
    for (auto [u, dir, e] : g[v]) {
        if (u == p) continue;
        if (!low[u]) {
            low[v] = min(low[v], dfs_low(u, v));
        } else {
            low[v] = min(low[v], in[u]);
        }
    }
    out[v] = T;
    return low[v];
}

bool is_parent(int u, int v) { return in[u] <= in[v] && out[u] >= out[v]; }

constexpr int LOG = 17;
int jmp[MAX_NODES][LOG];
void preprocess_lca() {
    for (int i = 0; i < MAX_NODES; i++) jmp[i][0] = par[i];
    for (int j = 1; j <= LOG; j++)
        for (int i = 0; i < MAX_NODES; i++) jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
}

int lca(int u, int v) {
    if (is_parent(u, v)) return u;
    if (is_parent(v, u)) return v;
    for (int i = LOG; i >= 0; i--)
        if (!is_parent(jmp[u][i], v)) u = jmp[u][i];
    return par[u];
}

bool share_component(int u, int v) {
    int l = lca(u, v);
    // Jak jeden jest przodkiem drugiego to jakaś krawędź powrotna z drugiego musi go przeskoczyć.
    if (l == u) return low[v] <= in[u];
    if (l == v) return low[u] <= in[v];

    // Jak nie są przodkami to musi z obu iść krawędź powrotna nad najniższego wspólnego przodka,
    // bo jakby tak nie było usunięcie go usunie wszystkie ścieżki z u do v.
    return low[u] < in[l] && low[v] < in[l];
}

constexpr int INF = 1e9;
int shortest_path(int src_v, int src_dir, int src_m, int dst_v) {
    vector dis(MAX_NODES, vector<int>(4, INF));
    dis[src_v][src_dir] = 0;
    deque<tuple<int, int, int>> q = {{src_v, src_dir, src_m}};
    while (!q.empty()) {
        auto [v, dir_v, m_v] = q.front();
        q.pop_front();
        if (v == dst_v) return dis[v][dir_v];
        for (auto [u, dir_u, e_u] : g[v]) {
            // Magazynier pcha paczkę.
            if (dir_u == inv(dir_v) && dis[u][dir_v] > dis[v][dir_v] + 1) {
                dis[u][dir_v] = dis[v][dir_v] + 1;
                q.emplace_back(u, dir_v, v);
            }

            // Magazynier obchodzi paczkę.
            if (share_component(u, m_v) && dis[v][dir_u] > dis[v][dir_v]) {
                dis[v][dir_u] = dis[v][dir_v];
                q.emplace_front(v, dir_u, u);
            }
        }
    }

    return INF;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    // Wczytać grida.
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> s[i];
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (bad(x, y)) continue;
            char c = s[x][y];
            if (c == 'M') m_x = x, m_y = y;
            if (c == 'P') p_x = x, p_y = y;
            if (c == 'K') k_x = x, k_y = y;

            if (!bad(x - 1, y)) {
                e[x - 1][y][DOWN] = e[x][y][UP] = ++E;
                int a = id(x - 1, y);
                int b = id(x, y);
                edges.emplace_back(a, b);
                g[a].emplace_back(b, DOWN, E);
                g[b].emplace_back(a, UP, E);
            }

            if (!bad(x, y - 1)) {
                e[x][y - 1][RIGHT] = e[x][y][LEFT] = ++E;
                int a = id(x, y - 1);
                int b = id(x, y);
                edges.emplace_back(a, b);
                g[a].emplace_back(b, RIGHT, E);
                g[b].emplace_back(a, LEFT, E);
            }
        }
    }

    // Znajdujemy po której stronie paczki jest magazynier.
    int dir = dfs_dir(id(m_x, m_y), id(p_x, p_y));
    if (dir == -1) {
        cout << "NIE\n";
        return 0;
    }

    dir = inv(dir);

    dfs_low(id(p_x, p_y), id(p_x, p_y));
    int len = shortest_path(id(p_x, p_y), dir, id(p_x + dx[dir], p_y + dy[dir]), id(k_x, k_y));
    if (len < INF)
        cout << len << "\n";
    else
        cout << "NIE\n";
}