// Rozwiązanie brutalne do zadania 'Turystyka' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(3^k * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 40 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define mask(S) for (int S = 0; S < (1 << h); S++)
using namespace std;
constexpr int MAXN = 20005, MAX_LEN = 10, INF = 10000000;
using DP = array<int, (1 << MAX_LEN)>;
vector<int> g[MAXN];
int vis[MAXN];

int c[MAXN], par[MAXN];
vector<int> P, P_idx(MAXN, -1);
// S - zbiór wierzchołków ze ścieżki, które są w dominating secie.
// D - zbiór wierzchołków ze ścieżki, które są zdominowane przez S.
void path_push(int v) {
    P_idx[v] = P.size();
    P.push_back(v);
}

void path_pop() {
    P_idx[P.back()] = -1;
    P.pop_back();
}

vector<int> sons[MAXN], ancestors[MAXN];

void split_edges(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) {
            split_edges(u);
            sons[v].push_back(u);
        } else {
            ancestors[v].push_back(u);
        }
    }
}

// Side note: może zamień tego dfs na for loopa od tyłu jak bedzie działać...
// Rekurencja * 1024 może zwiekszyć stałą kilkukrotnie.

// W zwracanych DP w S i D są tylko przodkowie v.
DP dfs_dp(int v, int S, int D) {
    path_push(v);

    // S jest już w stanie i w poddrzewach bedzie to samo takze w sumie wywalone...
    int h = P.size();
    DP dp_v;
    dp_v.fill(INF);
    dp_v[0] = 0;

    for (int u : sons[v]) {
        // Nie biorąc syna do domsetu.
        int S_no = S;
        int D_no = D;

        // Biorąc syna do domsetu.
        int S_yes = S + (1 << h);
        int D_yes = D + (1 << h);
        for (int p : ancestors[u]) {
            // Krawedz w dol...
            if (P_idx[p] == -1) continue;
            D_yes |= (1 << P_idx[p]);
            if (S >> P_idx[p] & 1) D_no |= (1 << h);
        }

        DP dp_u_no = dfs_dp(u, S_no, D_no);
        DP dp_u_yes = dfs_dp(u, S_yes, D_yes);

        DP new_dp;
        new_dp.fill(INF);
        // Interesują mnie tylko nadmaski D bo i tak już to dominuję.
        for (int D_final = D; D_final < (1 << h); D_final = (D_final + 1) | D) {
            for (int D_u = D_final;; D_u = (D_u - 1) & D_final) {
                int cost_u = min(dp_u_no[D_u], dp_u_yes[D_u]);
                new_dp[D_final] = min(new_dp[D_final], cost_u + dp_v[D_final - D_u]);
                if (D_u == 0) break;
            }
        }

        dp_v = new_dp;
    }

    // Liście mogą być zdominowane tylko przez S!
    if (sons[v].empty()) {
        dp_v.fill(INF);
        if (D >> (h - 1) & 1) {
            dp_v[D] = 0;
            if (S >> (h - 1) & 1) dp_v[D] += c[v];
        }

    } else {
        // Jak jestem w secie to trzeba za mnie zapłacić.
        if (S >> (h - 1) & 1)
            for (auto &i : dp_v) i += c[v];
        for (int D_final = 0; D_final < (1 << h); D_final++)
            if ((D_final >> (h - 1) & 1) == 0) dp_v[D_final] = INF;
    }

    // Propaguj miny po inkluzjach?
    for (int mask = (1 << h); mask >= 0; mask--) {
        for (int i = 0; i < h; i++) {
            if (mask >> i & 1) dp_v[mask ^ (1 << i)] = min(dp_v[mask ^ (1 << i)], dp_v[mask]);
        }
    }

    path_pop();

    return dp_v;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            split_edges(i);
            ans += min(dfs_dp(i, 0, 0)[1], dfs_dp(i, 1, 1)[1]);
        }
    }
    cout << ans << "\n";
}