// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + m * log(m))
// Złożoność pamięciowa: O(m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

constexpr int INF = 1'000'000'000;

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

    // Pierwsze elementy par trzymają długości ścieżek, drugie dokąd prowadzi pierwsza krawędź po nich.
    // dis[v] trzyma dwie najkrótsze ścieżki, które mają różniące się początki.
    vector dis(n+1, pair<pii, pii>({{INF, 1}, {INF, 1}}));

    priority_queue<tuple<int,int,int>> pq;
    for (auto [start, start_dis] : g[1]) {
        pq.push({-start_dis, start, start});
        dis[start].first = {start_dis, start};
    }

    int ans = INF;
    vector who_popped(n+1, vector<int>());
    while (!pq.empty()) {
        auto [d, v, from] = pq.top();
        pq.pop();
        d *= -1;
        // cerr << "d: " << d << " v: " << v << " from: " << from << "\n";
        if (v == 1) ans = min(ans, d);

        // TODO: Warunek na used, wierzchołek może przejrzec krawedzie tylko z dwoch roznych wierzchołków.
        if (who_popped[v].size() >= 2 || (who_popped[v].size() == 1 && who_popped[v].back() == from)) continue;
        who_popped[v].push_back(from);

        for (auto [u, w] : g[v]) {
            // Nie możemy wrócić do 1, bo przeszlibyśmy drugi raz tę samą krawędź.
            if (u == 1 && v == from) continue;
            int new_d = d + w;
            auto &[smallest_d, smallest_from] = dis[u].first;
            auto &[second_smallest_d, second_smallest_from] = dis[u].second;
            // cerr << "u: " << u << " new_d:" << new_d << "\n";
            if (new_d < smallest_d) {
                if (smallest_from == from) {
                    // Jeśli najkrótsza była z tego samego początku to mogę nadpisać tylko długość, żeby dwie najkrótsze nadal miały inne początki.
                    smallest_d = new_d;
                }
                else  {
                    // Jak początki były różne, to obecnie najlepsza staje się drugą najlepszą, a moja staje najlepszą i nadal mam dwie najlepsze o różnych początkach.
                    second_smallest_d = smallest_d;
                    second_smallest_from = smallest_from;
                    smallest_d = new_d;
                    smallest_from = from;
                }

                pq.push({-new_d, u, from});
            } else if (new_d < second_smallest_d && from != smallest_from) {
                second_smallest_d = new_d;
                second_smallest_from = from;
                pq.push({-new_d, u, from});
            }
        }
    }

    cout << ans << "\n";
}