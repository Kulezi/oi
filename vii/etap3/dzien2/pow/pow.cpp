// Rozwiązanie do zadania 'Powtórzenia' z III etapu VII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((suma po |s_i|) * log(max |s_i|)))
// Złożoność pamięciowa: O(suma po |s_i|)
// Punkty: 100 (upsolve)

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#define int long long
using namespace std;
constexpr int MAX_LEN = 2000, P = 31, MOD = 1'000'69'69'69, MAX_N = 10;
int h[MAX_N][MAX_LEN + 5], pot[MAX_LEN + 5];

int hasz(int i, int l, int r) {
    int res = (h[i][r] - 1LL * h[i][l - 1] * pot[r - l + 1]) % MOD;
    if (res < 0) res += MOD;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    pot[0] = 1;
    for (int i = 1; i <= MAX_LEN; i++) pot[i] = 1LL * pot[i - 1] * P % MOD;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int m = s[i].size();
        for (int j = 1; j <= m; j++) {
            h[i][j] = (1LL * h[i][j - 1] * P + s[i][j-1] - 'a' + 1) % MOD;
        }
    }

    auto check = [&](int len) {
        if (len == 0) return true;
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            set<int> rozne;
            int m = s[i].size();
            for (int start = 1; start + len - 1 <= m; start++) {
                rozne.insert(hasz(i, start, start + len - 1));
            }

            for (auto slowo : rozne) cnt[slowo]++;
        }

        for (auto [slowo, ile] : cnt)
            if (ile == n) return true;
        return false;
    };

    int l = 0, r = MAX_LEN;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (check(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << l << "\n";
}