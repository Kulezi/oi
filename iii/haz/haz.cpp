// Rozwiązanie do zadania 'Hazard' z II etapu III OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
constexpr int MAXN = 1005;
int n;

vector<int> g[MAXN];
int in[MAXN], out[MAXN], vis[MAXN], color[MAXN];

void no() {
    cout << "NIE\n";
    exit(0);
}

void dfs(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) dfs(u);
    }
}

deque<int> cycle;
int ban[MAXN];
bool find_cycle(int v) {
    color[v] = 1;
    cycle.push_back(v);
    for (auto u : g[v]) {
        if (u == n) continue;
        if (!color[u] && find_cycle(u)) return true;
        else if (color[u] == 1) {
            while (cycle.front() != u) cycle.pop_front();
            for (int i = 0; i < (int)cycle.size(); i++)
                ban[cycle[i]] = cycle[(i + 1) % cycle.size()];
            return true;
        }
    }
    color[v] = 2;
    cycle.pop_back();
    return false;
}

void yes(string why) {
    cerr << why << "\n";
    int v = 1;
    while (!g[v].empty()) {
        int u = g[v].back();
        g[v].pop_back();
        if (u == ban[v]) continue;
        cout << u << " ";
        v = u;
    }

    cout << "0\n";
    exit(0);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;

    if (n == 1) no();
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int j;
            cin >> j;
            in[j]++;
            out[i]++;
            g[i].push_back(j);
        }
    }

    // Sprawdzamy stopnie, żeby upewnić się czy graf jest eulerowski.
    for (int i = 1; i <= n; i++) {
        int need_out = in[i];
        if (i == 1)
            need_out++;
        else if (i == n)
            need_out--;
        // Nie jest, dowolna ścieżka zadziała.
        if (out[i] != need_out) yes("deg");
    }

    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (out[i] > 0 && !vis[i]) {
            // Graf nie jest spójny krawędziowo, czyli dowolna ścieżka
            // nie przejdzie przez tę krawędź.
            yes("connectivity");
        }
    }

    // Graf jest eulerowski i spójny krawędziowo.
    // Jedyna opcja to skończyć w n nieprzechodząc przez jakiś cykl niezawierający n.
    bool has_cycle = false;
    for (int i = 1; i < n; i++) {
        if (!color[i] && find_cycle(i)) {
            has_cycle = true;
            break;
        }
    }

    if (has_cycle) yes("cycle");
    else no();
}