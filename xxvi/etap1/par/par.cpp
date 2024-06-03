// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n+m) dla pojedyńczego testu.
// Punkty: 100

// https://codeforces.com/blog/entry/3107
#include <bits/stdc++.h>
const int MX = 100105;
using namespace std;
int q, n[2], x, a[MX][2], z[MX][2], res, X, Y;
inline void fin(int &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
inline void Z(int pos) {
    int L = 0, R = 0;
    for (int i = 1; i < n[pos]; i++) {
        if (i > R) {
            L = R = i;
            while (R < n[pos] && a[R - L + 1][pos] == a[R + 1][pos]) R++;
            z[i][pos] = R - L;
            R--;
        } else {
            int k = i - L;
            if (z[k][pos] < R - i + 1)
                z[i][pos] = z[k][pos];
            else {
                L = i;
                while (R < n[pos] && a[R - L + 1][pos] == a[R + 1][pos]) R++;
                z[i][pos] = R - L;
                R--;
            }
        }
    }
}
inline int okres(int pos, int len) {
    if (len == n[pos]) return 1;
    return z[len][pos] == n[pos] - len;
}
int main() {
    ios_base::sync_with_stdio(0);
    fin(q);
    while (q--) {
        res = X = Y = 0;
        fin(n[0]);
        fin(n[1]);
        for (int dim = 0; dim < 2; dim++)
            for (int i = 1; i <= n[dim]; i++) fin(a[i][dim]), a[i][dim] = (a[i][dim] & 1);
        for (int i = 1; i <= min(n[0], n[1]); i++) {
            X ^= a[i][0];
            Y ^= a[i][1];
            if (X == Y) res = i;
        }
        Z(0);
        Z(1);
        for (int i = min(n[0], n[1]); i > res; i--) {
            if (!okres(0, i) || !okres(1, i)) {
                res = i;
                break;
            }
        }
        cout << res << "\n";
    }
}