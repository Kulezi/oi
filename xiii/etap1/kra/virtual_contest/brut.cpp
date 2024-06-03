#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;


    vector<int> a(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ostatni = n;

    while (m--) {
        int szerokosc;
        cin >> szerokosc;

        for (int i = 1; i <= ostatni; i++) {
            if (a[i] < szerokosc) {
                ostatni = i-1;
                break;
            }
        }
        a[ostatni] = 0;
    }

    cout << ostatni << "\n";
}