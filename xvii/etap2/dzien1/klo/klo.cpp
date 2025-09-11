// Rozwiązanie do zadania 'Klocki' z II etapu XVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n) * m)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
int n, m;
int t[MAXN];
ll sum[MAXN], nadmiar_pref[MAXN], nadmiar_suf[MAXN];

inline ll suma(int l, int r) { return sum[r] - sum[l - 1]; }

int solve(int k) {
    vector<int> pozycje = {0};
    int wynik = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + t[i] - k;

        int l = 0, r = pozycje.size()-1;
        while (l < r) {
            int m = (l + r) / 2;
            if (sum[i] - sum[pozycje[m]] >= 0) r = m;
            else l = m + 1;
        }

        if (sum[i] - sum[pozycje[l]] >= 0) wynik = max(wynik, i - pozycje[l]);
        if (pozycje.empty() || sum[pozycje.back()] > sum[i]) pozycje.push_back(i);
    }

    return wynik;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i - 1] + t[i];
    }

    while (m--) {
        int k;
        cin >> k;
        cout << solve(k) << " ";
    }

    cout << "\n";
}
