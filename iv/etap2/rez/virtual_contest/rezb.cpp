#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    long long wynik = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool good = true;

        long long suma_pol = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            int pole_i = b[i] - a[i];
            for (int j = i+1; j < n; j++) {
                if (!(mask >> j & 1)) continue;
                int pole_j = b[j] - a[j];
                int przec_a = max(a[i], a[j]);
                int przec_b = min(b[i], b[j]);
                int pole_przec = max(0, przec_b - przec_a);
                if (pole_przec > 0) {
                    good = false;
                }
            }
            
            suma_pol += pole_i;
        }


        if (good) wynik = max(wynik, suma_pol);
    }

    cout << wynik << "\n";
    
}