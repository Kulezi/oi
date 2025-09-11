#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_A = 1'000'000, INF = MAX_A * 100, MAX_N = 100'005;
// Smallest prime divisor.
int f_div[MAX_A + 5];
vector<int> primes;

// "Nadmuchujemy bąbelki", tzn. zaczynamy z wierzchołkami wejściowymi i
// promieniami równymi 0. I jednocześnie zwiększamy promienie, wierzchołek jest
// najbliżej drugiego wtedy, gdy jego bąbelek dotknął drugiego bąbelka przed
// jakimikolwiek innymi, jak było wiele takich to bierzemy tej z niższym
// numerem.
int a[MAX_N], bubble[MAX_A + 5], ans[MAX_A + 5], shortest_dist[MAX_A + 5],
    second_occ[MAX_A + 5];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    queue<int> q;
    vector<int> dis(MAX_A + 5, INF);
    int max_a = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);

        if (!bubble[a[i]]) {
            bubble[a[i]] = i;
            shortest_dist[i] = INF;
            ans[i] = INF;

            dis[a[i]] = 0;
            q.push(a[i]);
        } else if (!second_occ[a[i]]) {
            second_occ[a[i]] = i;
        }
    }

    for (int i = 1; i <= max_a; i++) f_div[i] = i;
    for (int i = 2; i * i <= max_a; i++) {
        if (f_div[i] != i) continue;
        for (int j = i * i; j <= max_a; j += i)
            if (f_div[j] == j) {
                f_div[j] = i;
            }
    }

    for (int i = 1; i <= max_a; i++) {
        if (f_div[i] == i) primes.push_back(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        auto look_at_neighbour = [&](int u) {
            if (dis[u] > dis[v] + 1) {
                dis[u] = dis[v] + 1;
                bubble[u] = bubble[v];
                q.push(u);
            } else if (bubble[v] != bubble[u]) {
                int from = bubble[v];
                int to = bubble[u];
                int dis_from_to = dis[v] + dis[u] + 1;

                auto relax = [](int src, int dst, int d) {
                    if (shortest_dist[src] > d ||
                        (shortest_dist[src] == d && dst < ans[src])) {
                        ans[src] = dst;
                        shortest_dist[src] = d;
                    }
                };

                relax(from, to, dis_from_to);
                relax(to, from, dis_from_to);
            }
        };

        // Nie konstruujemy grafu, wyznaczamy sąsiadów na żywo.
        int k = v;
        while (k > 1) {
            int p = f_div[k];
            while (k % p == 0) k /= p;
            look_at_neighbour(v / p);
        }

        for (auto p : primes) {
            if (1LL * v * p > max_a) break;
            look_at_neighbour(v * p);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (second_occ[a[i]]) {
            if (i == bubble[a[i]])
                cout << second_occ[a[i]] << "\n";
            else
                cout << bubble[a[i]] << "\n";
        } else {
            cout << ans[i] << "\n";
        }
    }
}