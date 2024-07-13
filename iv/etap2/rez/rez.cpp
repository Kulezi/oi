// Rozwiązanie do zadania 'Rezerwacje sal wykładowych' z II etapu IV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(max(k_i)).
// Punkty: 100 (upsolve).

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXB = 30005;
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector konce(MAXB+1, vector<int>());
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        konce[a].push_back(b);
    }
    

    // dp[i] mówi ile maksymalnie czasu mogła być zajęta sala, tak, że w chwili i można zacząć wykład.
    vector<int> dp(MAXB+1, 0);
    for (int i = 0; i <= MAXB; i++) {
        if (i > 0) dp[i] = max(dp[i-1], dp[i]);
        for (auto j : konce[i]) {
            dp[j] = max(dp[j], dp[i] + j - i);
        }
    }
    
    cout << dp[MAXB] << "\n";
}