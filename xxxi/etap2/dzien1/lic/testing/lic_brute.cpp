// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n!)^m * n)
// Punkty: 0

// Rozwiązanie brutalne sprawdzające wszystkie kombinacje permutacji wskazań liczników.
// Zawsze daje poprawny wynik, ale działa tak wolno, że daje 0 punktów na szkopule.
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
constexpr int MAXN = 300'005;
constexpr ll INF = 1e18;

int c[MAXN];
vector<int> meters[MAXN];

int n, m;
ll ans = INF;
void bruteforce(int month) {
    if (month == m) {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += 1LL * (meters[m][i] - meters[0][i]) * c[i];
        }

        ans = min(ans, res);
        return;
    }

    sort(all(meters[month + 1]));
    do {
        bool good = true;
        for (int i = 0; i < n; i++) {
            if (meters[month][i] > meters[month + 1][i]) {
                good = false;
                break;
            }
        }
        if (good) {
            bruteforce(month + 1);
        }
    } while (next_permutation(all(meters[month + 1])));
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> c[i];

    for (int i = 0; i <= m; i++) {
        meters[i] = vector<int>(n);
        for (auto &j : meters[i]) cin >> j;
    }

    bruteforce(0);
    if (ans == INF) cout << "NIE\n", cerr << "NIE\n";
    else cout << ans << "\n";
}