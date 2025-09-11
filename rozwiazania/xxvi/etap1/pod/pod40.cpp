// Autor rozwiązania: Paweł Putra (pomysł: Mieszko Grodzicki)
// Złożoność czasowa: O(jakoś dużo).
// Punkty: 40 


#include <bits/stdc++.h>
#define int long long
using namespace std;
#define ll long long
ll n, q, makspdg, dp[1005];
string res;
vector<ll> factors;
string literki;
inline bool try_powers() {
    for (int i = 1; i <= 61; i++) {
        for (int j = 1; j < i; j++) {
            if ((1LL << i) - (1LL << j) == n) {
                for (int x = 1; x <= i; x++) cout << literki[x];
                cout << literki[j] << "\n";
                return 1;
            }
        }
    }
    return 0;
}
inline bool try_factors() {
    ll val = n;
    factors.clear();
    for (int i = 2; i <= 300; i++)
        while (val % i == 0) val /= i, factors.push_back(i);

    if (val > 1) factors.push_back(val);
    ll sum = 0;
    for (auto i : factors) sum += i;
    if (sum <= 300) {
        for (int i = 0; i < factors.size(); i++)
            for (int j = 1; j < factors[i]; j++) cout << literki[i];
        cout << "\n";
        return 1;
    }
    return 0;
}
void b(int A, int B, int pos) {
    if (makspdg == n + 1 || pos > 1000) return;
    if (dp[pos] == n) {
        cout << res << "\n";
        makspdg = n + 1;
        return;
    }
    int ra = dp[pos] * 2LL - dp[A - 1];
    int rb = dp[pos] * 2LL - (B == 0 ? 0 : dp[B - 1]);
    if (rand() % 2 == 0) {
        if (ra <= n) {
            res += "A";
            dp[pos + 1] = ra;
            b(pos + 1, B, pos + 1);
            res.pop_back();
        }
        if (rb <= n) {
            res += "B";
            dp[pos + 1] = rb;
            b(A, pos + 1, pos + 1);
            res.pop_back();
        }
    } else {
        if (rb <= n) {
            res += "B";
            dp[pos + 1] = rb;
            b(A, pos + 1, pos + 1);
            res.pop_back();
        }
        if (ra <= n) {
            res += "A";
            dp[pos + 1] = ra;
            b(pos + 1, B, pos + 1);
            res.pop_back();
        }
    }
}
main() {
    ios_base::sync_with_stdio(0);
    for (char i = 'a'; i <= 'z'; i++) literki += i;
    for (char i = 'A'; i <= 'Z'; i++) literki += i;
    for (char i = '0'; i <= '9'; i++) literki += i;
    cin >> q;
    while (q--) {
        cin >> n;
        if (try_factors()) {
        } else if (try_powers()) {
        } else {
            res = "A";
            makspdg = 2;
            dp[0] = 1;
            dp[1] = 2;
            b(1, 0, 1);
        }
    }
}