// Rozwiązanie do zadania 'Palindromy' z I etapu II OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
constexpr int INF = 1'000'000'000, MAXN = 205;
string s;

// -1 jak nie palindrom, 1 jak palindrom.
int palindrom[MAXN][MAXN];
bool czy_palindrom(int l, int r) {
    if (l > r) return true;
    if (palindrom[l][r] != 0) return palindrom[l][r] == 1;

    return palindrom[l][r] = (s[l - 1] == s[r - 1] && czy_palindrom(l + 1, r - 1));
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> s;

    int n = s.size();
    vector<int> mx(n + 1, -INF), mi(n + 1, INF), skad_mx(n + 1, 0), skad_mi(n + 1, 0);
    mx[0] = mi[0] = 0;
    for (int r = 1; r <= n; r++) {
        for (int l = r - 1; l >= 1; l -= 2) {
            if (!czy_palindrom(l, r)) continue;

            if (mx[l - 1] + 1 > mx[r]) {
                mx[r] = mx[l - 1] + 1;
                skad_mx[r] = l - 1;
            }
            if (mi[l - 1] + 1 < mi[r]) {
                mi[r] = mi[l - 1] + 1;
                skad_mi[r] = l - 1;
            }
        }
    }

    if (mx[n] < 0) {
        cout << "NIE\n";
        return 0;
    }

    auto wypisz = [&](auto &skad) {
        int i = n;
        vector<int> konce;
        while (i != 0) {
            konce.push_back(i);
            i = skad[i];
        }

        reverse(konce.begin(), konce.end());
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < konce.size() && i == konce[j]) {
                cout << " ";
                j++;
            }

            cout << s[i];
        }
        cout << "\n";
    };

    wypisz(skad_mi);
    wypisz(skad_mx);
}