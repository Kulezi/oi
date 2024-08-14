// Rozwiązanie do zadania 'Gońcy' z I etapu III OI.
// Implementacja wolniejszego algorytmu z 'Przygód Bajtazara'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define cerr if(false)cerr
using namespace std;
using Path = basic_string<int>;
constexpr int MAXN = 505;
vector<int> g[MAXN];

int color[MAXN];
Path s, cyc;
bool cycle(int v, int par) {
    color[v] = 1;
    s.push_back(v);
    for (auto u : g[v]) {
        if (!color[u] && cycle(u, v))
            return true;
        else if (color[u] && u != par && u == 1) {
            cyc = s.substr(s.find(u));
            return true;
        }
    }

    s.pop_back();
    return false;
}

ostream &operator<<(ostream &out, const Path &p) {
    out << "[";
    for (auto i : p) out << i << " ";
    out << "]";
    return out;
}

bool in[MAXN];
int n, m;
Path find_path(int from) {
    vector vis(n + 1, 0);
    Path res;
    auto dfs = [&](int v, auto &&self) -> void {
        vis[v] = 1;
        res += v;
        for (auto u : g[v]) {
            if (!vis[u] && !in[u]) {
                self(u, self);
                return;
            }
        }
    };

    dfs(from, dfs);

    return res;
}

vector<pair<int, int>> edges;
pair<int, int> find_neighbours(int u) {
    pair<int, int> res = {0, 0};
    for (auto v : g[u]) {
        if (in[v] && res.first == 0)
            res.first = v;
        else if (in[v])
            res.second = v;
    }

    return res;
}

void augment(int u) {
    Path p = find_path(u);
    int a = p.front();
    int b = p.back();
    auto [a_1, a_2] = find_neighbours(a);
    auto [b_1, b_2] = find_neighbours(b);

    int from = a_1;
    int to = (a_1 == b_1 ? b_2 : b_1);

    Path res;
    int i = 0;
    while (cyc[i] != from && cyc[i] != to) {
        res += cyc[i];
        i++;
    }

    if (cyc[i] == to) {
        swap(from, to);
        reverse(p.begin(), p.end());
    }

    res += from;
    i++;
    res += p;
    for (auto i : p) in[i] = 1;
    res += cyc.substr(i);

    cyc = res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        edges.emplace_back(a, b);
    }

    cycle(1, -1);
    for (auto i : cyc) in[i] = 1;
    while (cyc.size() < n) {
        for (auto [a, b] : edges) {
            if (in[a] && !in[b]) {
                augment(b);
                break;
            }
            else if (in[b] && !in[a]) {
                augment(a);
                break;
            }
        }
    }

    cout << 1;
    for (int i = 1; i < n; i++) cout << " " << cyc[i];
    cout << "\n";

    cout << 1;
    for (int i = n - 1; i > 0; i--) cout << " " << cyc[i];
    cout << "\n";
}