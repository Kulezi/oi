#include <bits/stdc++.h>
using namespace std;

int n;
int wrap(int x) {
    if (x == 0) return n;
    if (x == n + 1) return 1;
    return x;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;

    int suma = 0;
    vector<int> z(n + 1), d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> z[i] >> d[i];
        suma += z[i];
    }


    long long koszt = 0;
    
    int l = 1, r = 1;
    int d_l = 0, d_r = 0;
    int kupione = 1;

    int suma_l = z[l], suma_r = 0;
    while (kupione < n) {
        if (d_r + d[r] < d_l + d[wrap(l - 1)]) {
            // Idziemy w prawo z browaru.
            d_r += d[r];
            r = wrap(r + 1);
            koszt += d_r * z[r];
            suma_r += z[r];
        } else {
            // Idziemy w lewo z browaru.
            d_l += d[wrap(l - 1)];
            l = wrap(l - 1);
            koszt += d_l * z[l];
            suma_l += z[l];
        }


        kupione++;
    }

    
    cerr << 1 << " " << koszt << "\n";

    cerr << d_l << " " << d_r << "\n";
    long long wynik = koszt;
    for (int i = 2; i <= n; i++) {
        // cerr << suma_l << " " << suma_r << "\n";
        // Browary co poszły na lewo stają się o d[i-1] droższe.
        koszt += 1LL * suma_l * d[i-1];
        // cerr << i << " " << koszt << " LEWO \n";

        // Browary co poszły na prawo stają się o d[i-1] tańsze.
        koszt -= 1LL * suma_r * d[i-1];
        // cerr << i << " " << koszt << " PRAWO \n";

        // Do i-tego miasta wysylalismy w prawo, teraz jest za darmo (ale wysylamy za 0 w lewo).
        if (l != i) {
            suma_r -= z[i];
            suma_l += z[i];
            // cerr << suma_l << " " << suma_r << "+\n";
        }
        
        // Niektóre browary, do których szliśmy w lewo teraz bardziej opłaca się dowieźć idąc w prawo.
        // Możemy się po nich przeiterować idąc od lewej liniowo, takich przypadków będzie sumarycznie O(n).
        d_l += d[i-1], d_r -= d[i-1]; 
        while (d_r + d[r] < d_l) {
            assert(suma_l >= 0);
            assert(suma_r >= 0);
            assert(suma_l + suma_r == suma);
            koszt -= d_l * z[l];
            d_r += d[r], d_l -= d[l];
            l = wrap(l+1), r = wrap(r+1);
            suma_l -= z[r], suma_r += z[r];
            koszt += d_r * z[r];
            // cerr << d_l << " " << d_r << "\n";
        }

        cerr << i << " " << koszt << "\n";

        cerr << d_l << " " << d_r << "\n\n";
        wynik = min(wynik, koszt);
    }

    cout << wynik << "\n";
}