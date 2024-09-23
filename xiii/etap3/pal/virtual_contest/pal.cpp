// Rozwiązanie do zadania 'Palindromy' z III etapu XII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((suma dlugosci słów z wejścia) * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using H = pair<int, int>;
constexpr int MAX_LEN = 2'000'005, N_HASH = 2;
constexpr int MOD[N_HASH] = {1'000'69'69'69, 1'000'000'007}, P[N_HASH] = {31, 41};
int pot[N_HASH][MAX_LEN];
struct Word {
    int n;
    vector<vector<int>> h;
    Word() = default;
    Word(string s) : n(s.size()), h(N_HASH, vector<int>(n + 1, 0)) {
        for (int j = 0; j < N_HASH; j++)
            for (int i = 1; i <= n; i++) {
                h[j][i] = (1LL * h[j][i - 1] * P[j] + s[i - 1] - 'a' + 1) % MOD[j];
            }
    }

    H hash() { return {h[0][n], h[1][n]}; }
    H hash(int l, int r) { return {hash(l, r, 0), hash(l, r, 1)}; }
    int hash(int l, int r, int ktory) {
        int res = (h[ktory][r] - 1LL * h[ktory][l - 1] * pot[ktory][r - l + 1]) % MOD[ktory];
        if (res < 0) res += MOD[ktory];
        return res;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    for (int ktory = 0; ktory < N_HASH; ktory++) {
        pot[ktory][0] = 1;
        for (int i = 1; i < MAX_LEN; i++)
            pot[ktory][i] = 1LL * pot[ktory][i - 1] * P[ktory] % MOD[ktory];
    }

    int n;
    cin >> n;

    vector<string> slowa(n);
    vector<H> cnt;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m >> slowa[i];
        cnt.push_back(Word(slowa[i]).hash());
    }

    sort(cnt.begin(), cnt.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        Word w(slowa[i]);
        int m = w.n;

        // Ustalam gdzie jest środek palindromu.
        for (int mid = 1; mid <= m; mid++) {
            // Środek jest przed literką o pozycji mid, zliczamy palindromy parzyste.
            int l = mid - 1, r = m - mid + 1;
            // Długość palindromu który powinien być zawarty w i-tym słowie.
            int in = 2 * min(l, r);
            // Długość doklejanego kawałka.
            int add = m - in;
            if (w.hash(1, in) == w.hash(m - in + 1, m)) {
                H szukany = (l < r ? w.hash(1, add) : w.hash(m - add + 1, m));
                ans += binary_search(cnt.begin(), cnt.end(), szukany);
            }

            // Zliczamy palindromy nieparzyste o środku w mid.
            r--;
            in = 2 * min(l, r) + 1;
            add = m - in; 
            if (w.hash(1, in) == w.hash(m - in + 1, m)) {
                H szukany = (l < r ? w.hash(1, add) : w.hash(m - add + 1, m));
                ans += binary_search(cnt.begin(), cnt.end(), szukany);
            }
        }
    }

    cout << ans << "\n";
}