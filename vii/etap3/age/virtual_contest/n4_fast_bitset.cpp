#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 251, MAXD = MAXN * MAXN;

vector<int> g[MAXN];
bitset<MAXN> dasie[2][MAXD];
bitset<MAXN> ruch[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int p[2];
    cin >> p[0] >> p[1];

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        ruch[a][b] = 1;
    }

    dasie[0][0][p[0]] = 1;
    dasie[1][0][p[1]] = 1;

    // Ciekawe czy to sie da ubić xd.
    for (int d = 0; d < MAXD / 10; d++) {
        for (int s = 0; s < 2; s++) {
            for (int i = 1; i <= n; i++) {
                if (dasie[s][d][i]) dasie[s][d+1] |= ruch[i];
            }
        }

        bitset<MAXN> intersection = dasie[0][d] & dasie[1][d];
        if (intersection.count() > 0) {
            cout << d << "\n";
            return 0;
        }
    }

    cout << "NIE\n";
}
