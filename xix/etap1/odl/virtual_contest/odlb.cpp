#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_A = 1'000'000, INF = MAX_A * 100, MAX_N = 100'005;
// Smallest prime divisor.
int f_div[MAX_A + 5];
vector<int> g[MAX_A + 5];
int a[MAX_N], special[MAX_A + 5], idx[MAX_A + 5], idx2[MAX_A+5];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    int max_a = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }

    for (int i = 1; i <= max_a; i++) f_div[i] = i;
    for (int i = 2; i <= max_a; i++) {
        if (f_div[i] != i) continue;
        for (int j = i; j <= max_a; j += i) {
            if (f_div[j] == j) {
                f_div[j] = i;
            }
        }
    }

    for (int i = 2; i <= max_a; i++) {
        int m = i;
        while (m > 1) {
            int p = f_div[m];
            int j = i / p;
            g[i].push_back(j);
            g[j].push_back(i);
            while (f_div[m] == p) {
                m /= p;
            }
        }
    }

    auto bfs = [&](int start) {
        queue<int> q;
        vector<int> dis(max_a + 1, INF);
        dis[start] = 0;
        q.push(start);
        int best = n + 1, best_dist = INF;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : g[v]) {
                if (dis[u] > dis[v] + 1) {
                    dis[u] = dis[v] + 1;
                    if (special[u] && dis[u] < best_dist) {
                        best = idx[u];
                        best_dist = dis[u];
                    } else if (special[u] && dis[u] == best_dist) {
                        best = min(best, idx[u]);
                    }

                    q.push(u);
                }
            }
        }

        return best;
    };

    for (int i = 1; i <= n; i++) {
        if (!idx[a[i]]) {
            idx[a[i]] = i;
            special[a[i]] = 1;
        } else if (!idx2[a[i]]) {
            idx2[a[i]] = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        assert(bfs(a[i]) != i);
        if (idx2[a[i]]) {
            cout << (i == idx[a[i]] ? idx2[a[i]] : idx[a[i]]) << "\n";
        } else {
            cout << bfs(a[i]) << "\n";
        }
    }
}