// Rozwiązanie do zadania 'Rezerwacje sal wykładowych' z II etapu IV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + max(k_i))
// Złożoność pamięciowa: O(max(k_i))
// Punkty: 100 (upsolve)

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 30005;
vector<int> poczatki[MAXN];
int dp[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int p, k;
        cin >> p >> k;
        p++, k++;
        poczatki[k].push_back(p);
    }

    for (int k = 0; k < MAXN; k++) {
        dp[k] = dp[k - 1];
        for (auto p : poczatki[k]) dp[k] = max(dp[k], dp[p] + k - p);
    }

    cout << dp[MAXN - 1] << "\n";
}