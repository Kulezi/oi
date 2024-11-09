// Rozwiązanie do zadania 'Chomiki' z II etapu XVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3 * log(m) + n * (max z |s_i|))
// Złożoność pamięciowa: O(n^2 + suma po |s_i|)
// Punkty: 100
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
    string w = s[i] + "#" + s[j]; 
    if (i == j) w = s[i];

    int n = w.size();
    vector<int> P(n+1, 0);
    P[0] = -1;
    for (int i = 2; i <= n; i++) {
        int len = P[i-1];
        while (len >= 0 && w[len] != w[i-1]) len = P[len];
        P[i] = len + 1;
    }

    return P[n];
}

int n, m;

struct Mat {
    ll a[MAXN][MAXN];
    Mat(ll X) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++) a[i][j] = X;
    }
};

ll mi = INF;
Mat get_dp(int cnt) {
    Mat res(INF);

    if (cnt == 2) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                res.a[i][j] = s[i].size() + s[j].size() - overlap[i][j];
            }
        }
    }

    else if (cnt % 2 == 1) {
        Mat half = get_dp(cnt / 2 + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    res.a[i][k] = min(res.a[i][k], half.a[i][j] + half.a[j][k] - (int)s[j].size());
                }
            }
        }
    } else {
        Mat prev = get_dp(cnt - 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    res.a[i][k] = min(res.a[i][k], prev.a[i][j] + (int)s[k].size() - overlap[j][k]);
                }
            }
        }
    }

    return res;
}

int32_t main() {
    boost;
    cin >> n >> m;

    mi = INF;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        mi = min(mi, (ll)s[i].size());
    }

    if (m == 1) {
        cout << mi << "\n";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            overlap[i][j] = find_overlap(i, j);
        }
    }

    Mat res = get_dp(m);

    ll ans = INF;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) ans = min(ans, res.a[i][j]);
    cout << ans << "\n";
}
