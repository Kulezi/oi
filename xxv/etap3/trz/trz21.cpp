// Paweł Putra
// Złożoność czasowa: O(n^2)
// Punkty: 21

#include <bits/stdc++.h>
#define pref t
using namespace std;
int value[1005];
int t[3][1 << 20], ans, n;
string s;
bool checknie() {
    string s1 = "BCS";
    for (int i = 1; i <= 6; i++) {
        int gites = 1;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1] != s1[j % 3]) {
                gites = 0;
                break;
            }
        }
        if (gites) return 1;
        next_permutation(s1.begin(), s1.end());
    }
    return 0;
}
int main() {
    value['S'] = 0;
    ios_base::sync_with_stdio(0);
    value['B'] = 1;
    value['C'] = 2;
    cin >> n >> s;
    if (checknie()) {
        cout << "NIE";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        int c = value[s[i - 1]];
        t[0][i] = t[0][i - 1];
        t[1][i] = t[1][i - 1];
        t[2][i] = t[2][i - 1];
        t[c][i]++;
        for (int j = 1; j <= i && (i - j + 1 > ans); j++) {
            int a = pref[0][i] - pref[0][j - 1], b = pref[1][i] - pref[1][j - 1],
                c = pref[2][i] - pref[2][j - 1];
            if (a != b && b != c && a != c) {
                ans = max(ans, i - j + 1);
                //  cout << i << " " << j << endl;
                //  cout << a << " " << b << " " << c << endl;
            }
        }
    }
    cout << ans;
}