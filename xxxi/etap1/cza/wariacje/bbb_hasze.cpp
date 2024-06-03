#include <bits/stdc++.h>
using namespace std;
using Hash = int;

constexpr int B = 31, MAX_N = 1'000'005, MAX_ALPHA = 27;
constexpr int MOD = 1'000'000'007;

Hash h[MAX_N * MAX_ALPHA], pot[MAX_N * MAX_ALPHA];

Hash get_hash(int l, int r) {
    Hash res = (1LL * h[r] - 1LL * h[l-1] * pot[r-l+1]) % MOD;
    if (res < 0) res += MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);

    int n, k;
    long long a, b;
    cin >> n >> k >> a >> b;
    assert(n >= 2);
    assert(n <= 1'000'000);
    assert(n < a);
    assert(a < b);
    assert(b+1-a <= 1'000'000);
    assert(b <= (long long)1e18);

    string s;
    cin >> s;

    map<Hash, map<char, int>> occ;
    map<Hash, char> nxt;

    auto get_best = [&](Hash &substring) {
        char best = nxt[substring];
        if (best == 0) best = 'a';
        return best;
    };

    pot[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = (1LL * h[i-1] * B + s[i-1] - 'a' + 1) % MOD;
        pot[i] = 1LL * pot[i-1] * B % MOD;
    }


    for (int i = 1; i + k <= n; i++) {
        Hash substring = get_hash(i, i + k - 1);
        char c = s[i+k-1];
        occ[substring][c]++;
        char best = get_best(substring);
        if (occ[substring][c] > occ[substring][best] || (occ[substring][c] == occ[substring][best] && best > c)) nxt[substring] = c;
    }

    auto extend = [&]() -> char {
        Hash substring = get_hash(n - k + 1, n);
        char c = get_best(substring);
        n++;
        h[n] = (1LL * h[n-1] * B + c - 'a' + 1) % MOD;
        pot[n] = 1LL * pot[n-1] * B % MOD;
        return c;
    };

    while (n + 1 < a) {
        extend();
    }

    string ans;
    while (n < b) {
        char c = extend();
        ans += c;
    }

    cout << ans << "\n";
}