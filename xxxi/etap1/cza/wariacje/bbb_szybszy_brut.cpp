#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);

    int n, k;
    long long a, b;
    cin >> n >> k >> a >> b;
    assert(n >= 2);
    assert(n <= 1'000'000);
    assert(n < a);
    assert(a < b);
    assert(b <= (long long)1e18);

    string s;
    cin >> s;

    map<string, map<char, int>> occ;
    map<string, char> nxt;

    auto get_best = [&](string &substring) {
        char best = nxt[substring];
        if (best == 0) best = 'a';
        return best;
    };

    for (int i = 0; i + k < n; i++) {
        string substring = s.substr(i, k);
        char c = s[i+k];
        occ[substring][c]++;
        char best = get_best(substring);
        if (occ[substring][c] > occ[substring][best] || (occ[substring][c] == occ[substring][best] && best > c)) nxt[substring] = c;
    }

    auto extend = [&]() {
        string substring = s.substr(n-k);
        char c = get_best(substring);
        s += c;
        n++;
    };

    while (n + 1 < a) {
        extend();
    }

    string ans;
    while (n < b) {
        extend();
        ans += s.back();
    }

    cout << ans << "\n";
}