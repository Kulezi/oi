// Rozwiązanie zadania 'Podzielność' z I etapu XXIV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(B + q * log(B)).
// Złożoność pamięciowa: O(B).

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int32_t main() {
    int B, q;
    cin >> B >> q;


    int suma = 0;
    vector<int> ile(B);
    for (int i = 0; i < B; i++) {
        cin >> ile[i];

        suma += (1LL * ile[i] * i) % (B - 1);
        suma %= B - 1;
    }

    int reszta = suma % (B - 1);
    if (reszta > 0) {
        ile[reszta]--;
    }


    vector<ll> pref(B + 1, 0);
    pref[0] = ile[0];
    for (int i = 1; i < B; i++) {
        pref[i] = ile[i] + pref[i-1];
    }

    while (q--) {
        ll k;
        cin >> k;
        k++;

        if (k > pref[B - 1]) {
            cout << "-1\n"; 
            continue;
        }

        int l = 0, r = B - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (pref[m] >= k) r = m;

            else l = m + 1;
        }


        cout << l << "\n";
    }

}
