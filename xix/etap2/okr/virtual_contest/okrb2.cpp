// Rozwiązanie do zadania 'Okropny wiersz' z II etapu XIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * n)
// Złożoność pamięciowa: O(n)
// Punkty: 30 (upsolve)


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

int n;
string s;
Word w;

int okres(int l, int r) {
    int m = r - l + 1;
    for (int len = 1; len < m; len++) {
        if (m % len > 0) continue;
        if (w.hash(l, r - len) == w.hash(l + len, r)) return len;
    }
    
    return m;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> s;
    for (int ktory = 0; ktory < N_HASH; ktory++) {
        pot[ktory][0] = 1;
        for (int i = 1; i < MAX_LEN; i++)
            pot[ktory][i] = 1LL * pot[ktory][i - 1] * P[ktory] % MOD[ktory];
    }

    w = Word(s);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << okres(l, r) << "\n";
    }
}