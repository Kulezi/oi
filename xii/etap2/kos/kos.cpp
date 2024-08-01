// Rozwiązanie do zadania 'Kości' z II etapu XII OI.
// Implementacja wzorcówki z 'Przygód Bajtazara'.
// Autor implementacji: Paweł Putra
// Złożoność czasowa: O(m * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 10005;

int n, m;
vector<pair<int, int>> g[MAXN];
int src[MAXN], dst[MAXN], out[MAXN], flipped[MAXN];
void flip(int i) {
    swap(src[i], dst[i]);
    out[src[i]]++;
    out[dst[i]]--;
    flipped[i] ^= 1;
}

int searched;
int get_i_max() {
    int i_max = 1;
    for (int i = 1; i <= n; i++) {
        if (out[i] > out[i_max]) i_max = i;
    }
    return i_max;
}

int vis[MAXN], color = 1, rels;

bool dfs(int v) {
    vis[v] = color;
    for (auto &[u, i] : g[v]) {
        if (vis[u] != color && u == dst[i] && (out[u] <= searched || dfs(u))) {
            flip(i);
            return true;
        }
    }

    return false;
}

bool relax(int v) {
    color++;
    searched = out[v] - 2;
    return dfs(v);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
        src[i] = a;
        dst[i] = b;
        out[a]++;
    }

    int i_max = get_i_max();
    while (relax(i_max)) {
        while (relax(i_max));
        i_max = get_i_max();
    }

    cout << out[get_i_max()] << "\n";
    for (int i = 1; i <= m; i++) {
        cout << 1 - flipped[i] << "\n";
    }
}