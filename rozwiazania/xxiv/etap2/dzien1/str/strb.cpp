// Rozwiązanie brutalne do zadania 'Strajki' z II etapu XXIV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(m * n)
// Złożonośc pamięciowa: O(n)
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
constexpr int MAXN = 1'000'005;
int n, m;
int vis[MAXN], strajk[MAXN];
vector<int> g[MAXN];

void bfs(int s, int kolor) {
    vis[s] = kolor;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (vis[u] != kolor && !strajk[u]) {
                vis[u] = kolor;
                q.push(u);
            }
        }
    }
}

int policz_spojne() {
    static int K = 0;
    K++;
    int spojne = 0;
    for (int i = 1; i <= n; i++) {
        if (!strajk[i] && vis[i] != K) {
//            cerr << i << " ";
            spojne++;
            bfs(i, K);
        }
    } 
    //cerr << endl;

    return spojne;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        assert(a < b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cin >> m;
    while (m--) {
        int v;
        cin >> v;
        if (v > 0) {
            assert(!strajk[v]);
        } else assert(strajk[-v]);

        v = abs(v);
        strajk[v] = 1 - strajk[v];

        cout << policz_spojne() << "\n";
    }
}
