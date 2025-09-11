// Rozwiązanie do zadania 'Turystyka' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra, implementacja omówienia z 'niebieskiej książeczki'
// Złożoność czasowa: O((1 + sqrt(2))^t * (n + m)) gdzie t = długość najdłuższej ścieżki
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 20005, INF = 10000000, T = 10, MAXB = 1 << 10;
inline void mini(int& a, int b) { a = min(a, b); }
int c[MAXN], par[MAXN], vis[MAXN], dep[MAXN];
vector<int> g[MAXN], sons[MAXN], ancestors[MAXN];
vector<int> P;
array<int, MAXN> P_idx;

void path_push(int v) {
    P_idx[v] = P.size();
    P.push_back(v);
}

void path_pop() {
    P_idx[P.back()] = -1;
    P.pop_back();
}

void split_edges(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) {
            dep[u] = dep[v] + 1;
            split_edges(u);
            sons[v].push_back(u);
        } else if (dep[u] < dep[v]) {
            ancestors[v].push_back(u);
        }
    }
}

// dp[S][D] = min koszt zdominowania lewej części drzewa t.ż. stan interfejsu jest taki jak w:
// S - zbiór wierzchołków ze ścieżki, które są w dominating secie
// D - zbiór wierzchołków ze ścieżki, które są zdominowane
vector<vector<int>> dp_now, dp_future;
vector<pair<int, int>> good_masks[T + 2];

void dfs_dp(int v) {
    path_push(v);
    int h = P.size();

    for (auto [S, D] : good_masks[h]) dp_future[S][D] = INF;
    // Przerzucam v z B do S.
    for (auto [S, D] : good_masks[h - 1]) {
        int S_take = S | (1 << P_idx[v]), D_take = D | (1 << P_idx[v]);
        int S_no_take = S, D_no_take = D;
        for (auto p : ancestors[v]) {
            if (S >> P_idx[p] & 1)
                D_no_take |= (1 << P_idx[v]);
            else
                D_take |= (1 << P_idx[p]);
        }

        mini(dp_future[S_take][D_take], dp_now[S][D] + c[v]);
        mini(dp_future[S_no_take][D_no_take], dp_now[S][D]);
    }

    swap(dp_future, dp_now);
    for (auto u : sons[v]) {
        dfs_dp(u);
    }

    // Przerzucam v z S do A.
    for (auto [S, D] : good_masks[h - 1]) {
        dp_future[S][D] = INF;
    }

    for (auto [S, D] : good_masks[h]) {
        if (D >> P_idx[v]) {
            int D_headless = D ^ (1 << P_idx[v]);
            int S_headless = S ^ (S & (1 << P_idx[v]));
            mini(dp_future[S_headless][D_headless], dp_now[S][D]);
        }
    }

    swap(dp_future, dp_now);
    path_pop();
}

// Generuje wszystkie stany dynamika ze słów nad alfabetem {a,b,c},
// w których litery b i c nie sąsiadują.
void gen_masks(int mask_s, int mask_d, int i, string s) {
    if (s.back() == 'S' && s[s.size() - 2] == 'U') return;
    if (s.back() == 'U' && s[s.size() - 2] == 'S') return;
    good_masks[i].push_back({mask_s, mask_d});
    if (i == 10) return;

    int new_mask_s = mask_s << 1;
    int new_mask_d = mask_d << 1;
    gen_masks(new_mask_s | 1, new_mask_d | 1, i + 1, s + 'S');
    gen_masks(new_mask_s, new_mask_d, i + 1, s + 'U');
    gen_masks(new_mask_s, new_mask_d | 1, i + 1, s + 'D');
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    P_idx.fill(-1);

    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    gen_masks(0, 0, 0, "");

    int ans = 0;
    dp_future = dp_now = vector<vector<int>>(MAXB, vector<int>(MAXB, INF));
    dp_now[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            split_edges(i);
            dfs_dp(i);
        }
    }

    cout << dp_now[0][0] << "\n";
}
