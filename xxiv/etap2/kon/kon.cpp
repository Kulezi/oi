// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n+q) * sqrt(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
int sum[100605][315], ile, pos, dlug, n, q;
int t[100005];
int main() {
    cin >> n >> q;
    while (q--) {
        cin >> pos >> ile >> dlug;
        if (dlug > 310)
            for (int i = pos, cnt = 1; cnt <= ile; cnt++, i += dlug) t[i]++;
        else {
            sum[pos][dlug]++;
            sum[pos + (ile * dlug)][dlug]--;
        }
    }
    for (int i = 1; i <= 310; i++) {
        for (int j = 1; j <= n; j++) {
            if (j - i > 0) sum[j][i] += sum[j - i][i];
            t[j] += sum[j][i];
        }
    }
    for (int i = 1; i <= n; i++) cout << t[i] << " ";
}