#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;


    vector<int> a(n+1, 0), interesujacy(n+1, 1), lewo(n+1, 0);

    a[0] = 2e9;
    int najwezszy = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        lewo[i] = najwezszy;
        if (a[i] > a[najwezszy]) {
            interesujacy[i] = 0;
        } else if (a[i] < a[najwezszy]) {
            najwezszy = i;
        }
    }


    int ostatni = n;

    while (m--) {
        int szerokosc;
        cin >> szerokosc;

        for (int i = ostatni; i >= 1; i = lewo[i]) {
            if (interesujacy[i] && a[i] < szerokosc) {
                ostatni = i-1;
            }
            if (interesujacy[i] && a[i] > szerokosc) break;
        }

        a[ostatni] = 0;
        interesujacy[ostatni] = 1;
    }

    cout << ostatni << "\n";
}