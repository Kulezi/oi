// Rozwiązanie do zadania 'Okropny wiersz' z II etapu XIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * n^2)
// Złożoność pamięciowa: O(n)
// Punkty: 30 (upsolve)


#include <bits/stdc++.h>
using namespace std;
int n;
string s;

int okres(int l, int r) {
    int m = r-l+1;
    for (int len = 1; len < m; len++) {
        if (m % len > 0) continue;
        if (s.substr(l-1, m-len) == s.substr(l+len-1, m-len)) return len;
    }

    return m;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> s;
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << okres(l, r) << "\n";
    }
}