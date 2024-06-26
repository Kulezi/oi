// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (m * log(m)))
// Złożoność pamięciowa: O(m)
// Punkty: 60 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

constexpr int INF = 1'000'000'000;

// Po wejściu do jaskinii zawsze wrócimy do wejścia najkrótszą ścieżką nieużywającą korytarza, którym do niej weszliśmy.
// Najkrótsza ścieżka nie powtarza wierzchołków ani krawędzi, więc będzie zgodna z warunkami zadania.
// Sprawdzamy każdą krawędź i znajdujemy algorytmem Dijkstry długość najkrótszej ścieżki.
// Dodając wagę krawędzi do długości ścieżki dostajemy całą długość cyklu.
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector g(n+1, vector<pii>());
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        g[a].push_back({b, c});
        g[b].push_back({a, d});
    }

    int ans = INF;
    for (auto [start, start_dis] : g[1]) {
        vector<int> dis(n+1, INF), used(n+1, 0);
        dis[start] = start_dis;
        priority_queue<pii> pq;
        pq.push({-start_dis, start});
        
        while (!pq.empty()) {
            auto [_, v] = pq.top();
            pq.pop();
            if (used[v]) continue;
            used[v] = 1;

            for (auto [u, w] : g[v]) {
                // Ignorujemy krawędź, którą przyszliśmy.
                if (v == start && u == 1) continue;
                if (dis[u] > dis[v] + w) {
                    dis[u] = dis[v] + w;
                    pq.push({-dis[u], u});
                }
            }
        }

        ans = min(ans, dis[1]);
    }

    cout << ans << "\n";
}