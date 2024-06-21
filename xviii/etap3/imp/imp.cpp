// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 3005;
bitset<MAXN> g[MAXN], used;
int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a][b] = g[b][a] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && !used[i] && !used[j] && !g[i][j]) {
                used[i] = used[j] = 1;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            cout << i << " ";
            cnt++;
        }

        if (cnt == n / 3) break;
    }
}