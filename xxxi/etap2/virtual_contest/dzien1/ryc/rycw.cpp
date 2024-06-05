// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^k * (n + m) * k * log(n))
// Punkty: 75
#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = " << x << " " ;
#define n() cerr << endl;
using namespace std;

constexpr int MAXK = 10, MAXN = 10005,  BIN = 1'000'000'000;
int n, m, d, k;

vector<pair<int, vector<int>>> g[MAXN];
vector<pair<int, int>> g2[MAXN];

vector<int> ans;

int vis[MAXN][1<<MAXK];
int COLOR;
bool check(int mid, int bit) {
    // dbg(mid); dbg(bit); n();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            g2[i][j].second = 0;
            for (int kk = 0; kk <= bit; kk++) {
                if (g[i][j].second[kk] >= ans[kk]) g2[i][j].second |= (1 << kk);
            }
        }
    }


    int szukany = (1 << (bit+1))-1;
    ++COLOR;
    queue<tuple<int,int,int>> q;
    q.push({1, 0, 0});
    while (!q.empty()) {
        auto [v, orek, odleglosc] = q.front();
        q.pop();
        if (odleglosc == d) return false;


        for (auto &[u, w] : g2[v]) {
            int norek = orek | w;
            if (u == n && norek == szukany) {
                return true;
            }

            if (vis[u][norek] != COLOR) {
                vis[u][norek] = COLOR;
                q.push({u, norek, odleglosc+1});
            }
        }

    }

    return false;
}

// Chcę liczyć takie coś:
// Dla każdej ścieżki w której i-ty miecz będzie miał wartość >= t
// istnieje taka krawędź u-v, na której w(uv)_i >= t, że
// dist(1, u, m1) + dist(v, n, m2) + 1 <= d, że m1 | m2 = zapalone i+1 pierwszych bitów
// Jak mam wyliczone dist(1, u, m), to chcę wyliczyć 
// dist'(1, u, m) = min(dist(1, u, m | x)) bedace maksem z wyszystkich
// Mogę to zrobić np. forem po maskach od 0 do 2^n 

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> m >> d >> k;

    ans = vector<int>(k, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        vector<int> rzemieslnik(k, 0);
        for (auto &j : rzemieslnik) cin >> j;

        g[u].emplace_back(v, rzemieslnik);
        g[v].emplace_back(u, rzemieslnik);
        g2[u].emplace_back(v, 0);
        g2[v].emplace_back(u, 0);
    }

    for (int bit = 0; bit < k; bit++) {
        int lo = 0, hi = BIN;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            ans[bit] = mid;
            if (check(mid, bit)) {
                lo = mid;
            } else {
                hi = mid-1;
            }
        }

        n();
        ans[bit] = lo;
        cout << lo << " ";
    }

    cout << "\n";
}