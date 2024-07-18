// Rozwiązanie do zadania 'Suma cyfr' z II etapu XXIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(MAX_LEN * (s * m + q))
// Złożoność pamięciowa: O(MAX_LEN * s * m)
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAX_SUM = 210, MAX_LEN = 200, MAX_MOD = 200, MAX_DIGIT = 10;
constexpr ll INF = 1e18;

void cap(ll &x) {
    if (x > INF) x = INF;
}

ll dp[MAX_LEN+1][MAX_SUM+1][MAX_MOD];

int pot10[MAX_LEN];

int s, m, q;
ll get_dp(int len, int sum, int r, int digit) {
    int old_sum = sum - digit;
    if (old_sum < 0) return 0;
    int old_r = (r - digit * pot10[len - 1] % m + m) % m;
    return dp[len-1][old_sum][old_r];
}

int32_t main() {
    cin >> s >> m >> q;
    dp[0][0][0] = 1;
    pot10[0] = 1;
    for (int i = 1; i < MAX_LEN; i++) pot10[i] = pot10[i - 1] * 10 % m;

    for (int len = 0; len + 1 <= MAX_LEN; len++) {
        for (int sum = 0; sum <= s; sum++) {
            for (int rem = 0; rem < m; rem++) {
                for (int digit = 0; digit < MAX_DIGIT; digit++) {
                    dp[len + 1][sum][rem] += get_dp(len+1, sum, rem, digit);
                    cap(dp[len + 1][sum][rem]);
                }
            }
        }
    }

    while (q--) {
        ll k;
        cin >> k;

        if (dp[MAX_LEN][s][0] < k) {
            cout << "NIE\n";
            continue;
        }

        int sum = s;
        int r = 0;
        bool leading_zero = true;
        for (int len = MAX_LEN; len > 0; len--) {
            for (int d = 0; d < MAX_DIGIT; d++) {
                if (get_dp(len, sum, r, d) >= k) {
                    if (d != 0) leading_zero = false;
                    if (d != 0 || !leading_zero) {
                        cout << d;
                    }

                    r = (r - (pot10[len - 1] * d) % m + m) % m;
                    sum -= d;
                    break;
                } else {
                    k -= get_dp(len, sum, r, d);
                }
            }
        }

        cout << "\n";
    }
}