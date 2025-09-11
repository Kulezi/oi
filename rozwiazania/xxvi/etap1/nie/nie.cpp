// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(|A|^2 * n).
// Punkty: 100

#include <bits/stdc++.h>
#define boost                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define wypisz(x) cerr << #x << " = " << x << "\n"
#define ll long long
#define ld long double
#define pii pair<int, int>
using namespace std;
string s[2], res, A = "GTAC";
int n[2], now[505], m, val[505], lewy[2], prawy[2], drugie[2], posuw;
vector<int> last[2];
inline void gemacht(int pos) {
    cin >> s[pos];
    n[pos] = s[pos].size();
    for (auto i : A) now[i] = n[pos] + 1;
}
inline void getlast(int pos) {
    int cur = m;
    last[pos] = {n[pos]};
    for (int i = n[pos]; i > 0; i--)
        if (cur > 0 && s[pos][i - 1] == res[cur - 1]) last[pos].push_back(i), cur--;
    lewy[pos] = 1;
    drugie[pos] = 1;
}
inline bool check(int &ch, string &fixed) {
    for (int i = 0; i < 2; i++)
        while (drugie[i] < lewy[i] || (drugie[i] <= n[i] && s[i][drugie[i] - 1] != A[ch]))
            drugie[i]++;
    for (int i = 0; i < 2; i++)
        if (lewy[i] > n[i] || drugie[i] > prawy[i]) return 0;
    fixed += A[ch];
    return 1;
}
inline void fix(int ch) {
    m = res.size();
    string fixed;
    getlast(0), getlast(1);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 2; j++) prawy[j] = last[j].back(), last[j].pop_back();
        while (check(ch, fixed))
            for (int j = 0; j < 2; j++) {
                while (s[j][lewy[j] - 1] != A[ch]) lewy[j]++;
                lewy[j]++;
            }
        if (i < m) fixed += res[i];
        for (int j = 0; j < 2; j++) {
            while (s[j][lewy[j] - 1] != res[i]) lewy[j]++;
            lewy[j]++;
        }
    }
    res = fixed;
}
int main() {
    boost;
    for (int i = 0; i < 4; i++) val[A[i]] = i;
    gemacht(0), gemacht(1);
    for (auto i : A) fix(val[i]);
    cout << res;
}