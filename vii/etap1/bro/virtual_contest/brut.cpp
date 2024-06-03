#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
int wrap(int x) {
    if (x == 0) return n;
    if (x == n+1) return 1;
    return x;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;

    vector<int> z(n+1), d(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> z[i] >> d[i];
    }


    long long wynik = 1e18;
    for (int i = 1; i <= n; i++) {
        long long koszt = 0;
        int l = i, r = i;
        int d_l = 0, d_r = 0;
        int kupione = 1;
        while (kupione < n) {
            if (d_r + d[r] < d_l + d[wrap(l-1)]) {
                // idziemy w prawo.
                d_r += d[r];
                r = wrap(r+1);
                koszt += d_r * z[r];
            } else {
                // idziemy w lewo.
                d_l += d[wrap(l-1)];
                l = wrap(l-1);
                koszt += d_l * z[l];
            }   
            kupione++;
        }

        cerr << i << " " << koszt << "\n";
        wynik = min(wynik, koszt);
    }

    cout << wynik << "\n";
}