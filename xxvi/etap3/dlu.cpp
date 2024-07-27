// Rozwiązanie do zadania 'Długie podróże' z III etapu XXVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(|V| * (n + m + p))
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
constexpr int INF = 1'000'000'000, MAX_OPS = 1'000'000'00;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    srand(R(1, INF));
    ios_base::sync_with_stdio(0);
    int n, m, p;
    cin >> n >> m >> p;

    vector g(n+1, vector<int>());
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<tuple<int,int,int>> zapytania(p, {0, 0, INF});
    for (auto &[s, t, odp] : zapytania) cin >> s >> t;

    int V = min(n, MAX_OPS / (n+m+p));
    vector<int> losowe(n);
    iota(all(losowe), 1);
    random_shuffle(all(losowe));
    losowe.resize(V);


    // Najkrótsza ścieżka ma conajmniej n/10 wierzchołków.
    // X - losowy wierzchołek jest na tej ścieżce.
    // => P[X] >= (n/10) / n = 1/10
    
    // V - zbiór losowych wierzchołków.
    // Y - jakikolwiek wierzchołek z V jest na tej ścieżce. 
    // => P[Y] >= 1 - P[~X]^|V|.

    // Z = wszystkie najkrótsze ścieżki z zapytań będą przechodzić przez jakiś wierzchołek z V.
    // P[Z] >= P[Y]^p.

    // Mamy czas O(|V|*(n + m + p)).
    // Limit to 4s, max punktów za 2s, celujemy w bezpieczną sekundę to 10^8 operacji, n+m+p <= 5*10^5.
    // To maksymalne |V| co się zmieści w limit to będzie ~200.

    // P[Z] = P[Y]^2e5 = (1 - (9/10)^200)^2e5.
    // Python mówi, że P[Z] dla |V| = 300 > 0.999, spoko.

    for (auto x : losowe) {
        vector<int> dis(n+1, INF);
        dis[x] = 0;
        queue<int> q;
        q.push(x);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : g[v]) {
                if (dis[u] > dis[v] + 1) {
                    dis[u] = dis[v] + 1;
                    q.push(u);
                }
            }
        }

        for (auto &[s, t, odp] : zapytania) {
            odp = min(odp, dis[s] + dis[t]);
        }
    }

    for (auto [s, t, odp] : zapytania) cout << odp << "\n";
}