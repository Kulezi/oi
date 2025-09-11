// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005;
vector<int> g[MAXN];
int who[MAXN][MAXN];

// dp[poddrzewo][ile wierzchołków trójkąta już wybrałem] =
// max liczba przeciętych trójkątów, tak, że przekątne trójkąta przecinają
// trójkąt korzenia.
std::array<int, 4> dp[MAXN];
int ans;
void dfs(int v, int par) {
    // Wierzchołki są w jednym poddrzewie.
    for (auto u : g[v]) {
        if (u == par) continue;
        dfs(u, v);

        auto new_dp = dp[v];
        auto old_dp = dp[v];
        new_dp[1] = max(new_dp[1], dp[u][1]);
        new_dp[2] = max(new_dp[2], dp[u][2]);
        new_dp[2] = max(new_dp[2], old_dp[1] + dp[u][1]);
        new_dp[3] = max(new_dp[3], old_dp[2] + dp[u][1]);
        new_dp[3] = max(new_dp[3], old_dp[1] + dp[u][2]);
        swap(new_dp, dp[v]);
    }

    for (int i = 1; i <= 3; i++) dp[v][i]++;
    ans = max(ans, dp[v][3]);
}

void add_edge(int a, int b, int face) {
    if (a > b) swap(a, b);
    if (!who[a][b]) {
        who[a][b] = face + 1;
    } else {
        g[face].push_back(who[a][b] - 1);
        g[who[a][b] - 1].push_back(face);
    }
}

int32_t main() {
    int n;
    cin >> n;

    int n_triangles = n - 2;
    for (int i = 0; i < n_triangles; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, i);
        add_edge(b, c, i);
        add_edge(a, c, i);
    }

    dfs(0, -1);

    cout << ans << "\n";
}
