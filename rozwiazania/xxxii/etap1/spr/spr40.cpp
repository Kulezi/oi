// Rozwiązanie podgrupy 3 zadania 'Sprawiedliwy podział' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 40 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
constexpr int MAXN = 500005, INF = 2'000'000'000;
int n;
int a[MAXN], b[MAXN], res[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    long long sum_a = 0, sum_b = 0;
    int min_a = INF, min_b = 0;

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(ord.begin(), ord.end(), [&](int lhs, int rhs) { return a[lhs] > a[rhs]; });
    for (int i = 0; i < n; i++) {
        sum_a += a[i];
        min_a = min(min_a, a[i]);
    }

    for (auto i : ord) {
        if (sum_b < sum_a - min_a && sum_a - a[i] >= sum_b) {
            sum_a -= a[i];
            sum_b += a[i];
            min_b = a[i];
            res[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) cout << 1 - res[i] << " ";
    cout << "\n";
}