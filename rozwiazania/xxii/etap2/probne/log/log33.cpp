// Rozwiązanie zadania 'Logistyka' z II etapu XXII OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n * m)
// Złożoność pamięciowa: O(n).
// Punkty: 33


#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
int A[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) A[i] = 0;

    for (int i = 1; i <= m; i++) {
        char typ;
        cin >> typ;
        if (typ == 'U') {
            int k, a;
            cin >> k >> a;
            A[k] = a;
        } else {
            int c, s;
            cin >> c >> s;
            ll suma = 0;
            for (int i = 1; i <= n; i++) {
                suma += min(s, A[i]);
            }

            cout << suma << endl;
            // if (suma >= 1LL * c * s) cout << "TAK\n";
            // else cout << "NIE\n";
        }
    }
}

