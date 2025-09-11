// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 300005;

int n, a, b, vis[MAXN], dist[MAXN], mx;
vector<int> g[MAXN];

long long dfs(int v, int builders) {
    vis[v] = builders;
    long long sum = 0;
    for (auto u : g[v]) {
        if (vis[u] != builders) {
            sum += dfs(u, builders) + 1;
        }
    }

    return max(0LL, sum - builders);
}

bool check(int builders) { return dfs(1, builders) == 0; }
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int l = 1, r = n;
    int mid = (l + r) >> 1;
    while (l != r) {
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
        mid = (l + r) >> 1;
    }
    if (n == 1) mid = 0;
    cout << mid;
}