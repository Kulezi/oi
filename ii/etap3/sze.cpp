// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 10005;
long double a[MAXN], b[MAXN];
int ord[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    int start = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        if (b[i] == 0) {
            ord[start++] = i;
        }
    }

    int j = start;
    for (int i = 1; i <= n; i++) {
        if (b[i] > 0) {
            ord[j++] = i;
        }
    }

    if (start != n) {
        sort(ord + start, ord + n + 1,
             [&](int lhs, int rhs) { return a[lhs] * b[rhs] > a[rhs] * b[lhs]; });
    }

    for (int i = 1; i <= n; i++) cout << ord[i] << "\n";
}