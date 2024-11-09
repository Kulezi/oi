// Rozwiązanie wolne do zadania 'Chomiki' z II etapu XVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2 * (max z |s_i|) + n^2 * m)
// Złożoność pamięciowa: O(n^2 + suma po |s_i|)
// Punkty: 36
#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define ALL(x) (x).begin(), (x).end()
using namespace std;

#define dbg(x) #x << " = " << x << " "
#define gdzie __FILE__ << ":" << __LINE__
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
constexpr int MAXN = 205;
constexpr ll INF = 1e18;
string s[MAXN];
int overlap[MAXN][MAXN];

int find_overlap(int i, int j) {
    for (int len = min(s[i].size(), s[j].size()) - (i == j); len > 0; len--) {
        if (s[i].substr(s[i].size() - len) == s[j].substr(0, len)) {
            return len;
        }
    }

    return 0;
}

int32_t main() {
    boost;
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            overlap[i][j] = find_overlap(i, j);
        }
    }

    vector<ll> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= m; i++) {
        vector<ll> new_dp(n+1, INF);
        for (int cur = 1; cur <= n; cur++) {
            for (int old = 0; old <= n; old++) {
                new_dp[cur] = min(new_dp[cur], dp[old] + (int)s[cur].size() - overlap[old][cur]);
            }
        }

        swap(dp, new_dp);
    }

    cout << *min_element(ALL(dp)) << "\n";
}
