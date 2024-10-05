// Rozwiązanie do zadania 'Zapiekanki' z III etapu XXIV OI.
// Implementacja wzorcówki z 'Przygód Bajtazara'
// Autor: Paweł Putra
// Złożoność czasowa: O(k^2)
// Złożoność pamięciowa: O(k)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr ll INF = 1e15;

bool ostatnim(ll t, int zap, ll koniec) { return zap > 0 && t <= koniec; }

bool nowym(ll t, ll koniec, int d, ll t_j) { return t <= koniec + d && koniec + d < t_j - d; }

int32_t main() {
    ios_base::sync_with_stdio(0);
    int k, z, d;
    cin >> k >> z >> d;

    vector<ll> t(k + 2, 0);
    vector<ll> pt(k + 2, 0);
    long long wynik = 0;
    for (int i = 1; i <= k; i++) {
        cin >> t[i];
        if (t[i] < d) {
            wynik += d - t[i];
            t[i] = d;
        }

        pt[i] = pt[i - 1] + t[i];
    }

    t[k + 1] = INF;
    pt[k + 1] = pt[k] + t[k + 1];

    vector<ll> dp(k + 2, INF);
    dp[k + 1] = 0;
    for (int i = k; i >= 0; i--) {
        ll koszt = 0;
        ll koniec = t[i];
        ll zap = 0;
        int ostatni = i;

        // W którym miejscu zaczyna się następny blok.
        for (int j = i + 1; j <= k + 1; j++) {
            while (ostatni + 1 < j && (ostatnim(t[ostatni + 1], zap, koniec) ||
                                       nowym(t[ostatni + 1], koniec, d, t[j]))) {
                if (ostatnim(t[ostatni + 1], zap, koniec)) {
                    zap = zap - 1;
                } else {  // nowym
                    zap = z - 1;
                    koniec = koniec + d;
                }
                koszt = koszt + koniec - t[ostatni + 1];
                ostatni++;
            }

            if (koniec < t[j] - d && j - ostatni <= z) {
                ll koszt_nast = 1LL * (j - ostatni) * t[j] - (pt[j] - pt[ostatni]);
                dp[i] = min(dp[i], dp[j] + koszt + koszt_nast);
            }
        }
    }

    wynik += dp[0];
    cout << wynik << "\n";
}