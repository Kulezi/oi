// Rozwiązanie do zadania 'Okropny wiersz' z II etapu XIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + q * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <string>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using H = int;

constexpr int MAX_LEN = 500'005;
constexpr int MOD = 1'000'69'69'69, P = 31;
int pot[MAX_LEN], h[MAX_LEN];
int hasz(int l, int r) {
    int res = (h[r] - 1LL * h[l - 1] * pot[r - l + 1]) % MOD;
    if (res < 0) res += MOD;
    return res;
}

int n;
string s;

int czyn[MAX_LEN];

bool ma_okres(int l, int r, int len) { return hasz(l, r - len) == hasz(l + len, r); }
int okres(int l, int r) {
    int m = r - l + 1;
    int k = m;
    while (k > 1) {
        int p = czyn[k];
        if (ma_okres(l, l + m - 1, m / p)) {
            m /= p;
        }
        k /= p;
    }

    return m;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> s;

    for (int i = 1; i <= n; i++) czyn[i] = i;
    for (int i = 2; i * i <= n; i++)
        if (czyn[i] == i)
            for (int j = i * i; j <= n; j += i) czyn[j] = i;

    pot[0] = 1;
    for (int i = 1; i <= n; i++) {
        pot[i] = 1LL * pot[i - 1] * P % MOD;
        h[i] = (1LL * h[i - 1] * P + s[i - 1] - 'a' + 1) % MOD;
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << okres(l, r) << "\n";
    }
}