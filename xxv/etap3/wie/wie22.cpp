// Paweł Putra
// Złożoność czasowa: O(n^2)
// Punkty: 22

// Wylicza brutalnie wartości wielomianów, ale obcina cykle, żeby było szybciej.
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, q, a[1337000], sumres, potq[1337000], sum[1337000], pote = 1, cykl;
vector<int> v;
int getval(int x) {
    int pot = 1, res = 0;
    // cerr << "CALC " << x  << endl;
    int pocz = n;
    for (int i = 2; i <= n; i++) {
        pot *= x;
        pot % m;
        if (pot == 1) {
            pocz = i;
            break;
        }
    }
    res = (sum[n] - sum[pocz - 1]) % m;
    for (int j = pocz - 1; j >= 1; j--) {
        res *= x;
        res %= m;
        res += a[j];
        res %= m;
    }
    return res;
}
main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    potq[0] = 1;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {  // a[i]=i;
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        pote *= q;
        pote %= m;
        int xd = getval(pote);
        v.push_back(xd);
        if (pote == 1) {
            cykl = i;
            break;
        }
    }
    while (v.size() != n) v.push_back(v[v.size() % cykl]);
    for (auto i : v) sumres += i, sumres %= m;
    cout << sumres << "\n";
    for (auto i : v) cout << i << " ";
}