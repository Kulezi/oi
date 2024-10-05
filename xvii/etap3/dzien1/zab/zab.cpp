// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve, pierwszy submit)

#include <iostream>
#include <vector>
#include <deque>
using namespace std;
using ll = long long;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    ll m;
    cin >> n >> k >> m;

    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto d = [&](int i, int j) {
        return llabs(a[i] - a[j]);
    };


    vector g_rev(n+1, vector<int>());
    vector g(n+1, 0);

    // Utrzymujemy jaki jest przedział k najbliższych kamieni gąsienicą.
    int l = 1, r = k + 1;
    for (int i = 1; i <= n; i++) {
        while (r + 1 <= n && d(r+1, i) < d(l, i)) {
            l++;
            r++;
        }

        int jump = l;
        // W prawo skaczemy tylko jak to najdalszy kamień i nie ma remisu.
        if (d(r, i) > d(l, i)) jump = r;
        
        g[i] = jump;
        g_rev[jump].push_back(i);
    }

    vector<int> vis(n+1, 0), on_cycle(n+1, 0), ans(n+1);
    for (int i = 1; i <= n; i++) {
        // Chcę znaleźć po pierwsze cykl, a potem przejść po wszystkich wierzchołkach na nim.
        if (vis[i]) continue;
        
        deque<int> cycle, path;
        int v = i;
        while (!vis[v]) {
            vis[v] = 1;
            cycle.push_back(v);
            v = g[v];
        }
        
        while (cycle.front() != v) cycle.pop_front();
        for (auto i : cycle) on_cycle[i] = 1;

        int cycle_len = (int)cycle.size();

        auto find_finish = [&](int v, auto &&self) -> void {
            vis[v] = 1;
            path.push_front(v);

            int len = (int)path.size();
            if (len > m) ans[v] = path[m];
            else {
                // Podchodzę do wejścia na cykl skacząc len-1 razy.
                ll rem = m - (len - 1);
                rem %= cycle_len;
                ans[v] = cycle[rem];
            }

            for (auto u : g_rev[v]) {
                if (!on_cycle[u])
                    self(u, self); 
            }

            path.pop_front();
        };

        for (int i = 0; i < cycle_len; i++) {
            find_finish(cycle.front(), find_finish);
            cycle.push_back(cycle.front());
            cycle.pop_front();
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}