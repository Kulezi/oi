// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: ??? (brut)

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'005;
int n, m;

vector<int> g[MAXN * 3];

int oryginal(int v) {
    return 4 * v;
}

int parzyste(int v) {
    return 4 * v + 1;
}

int nieparzyste(int v) {
    return 4 * v + 2;
}

int koniec(int v) {
    return 4 * v + 3;
}

bool jest_koncem(int v) {
    return v % 4 == 3;
}

int bfs(int start) {
    vector<int> vis(koniec(n)+5, 0);
    vis[start] = 1;
    queue<int> q;
    q.push(start);

    int reachable = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (jest_koncem(v)) reachable++;
        for (auto u : g[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                q.push(u);
            }
        }
    }

    return reachable;
}



int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;

    for (int a = 1; a <= n; a++) {
        g[oryginal(a)].push_back(parzyste(a));
        g[oryginal(a)].push_back(nieparzyste(a));

        g[parzyste(a)].push_back(koniec(a));
        g[nieparzyste(a)].push_back(koniec(a));
    }


    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;

        g[nieparzyste(a)].push_back(nieparzyste(b));
        g[parzyste(b)].push_back(parzyste(a));
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (bfs(oryginal(i)) == n) ans.push_back(i);
    }

    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }

    cout << "\n";
}