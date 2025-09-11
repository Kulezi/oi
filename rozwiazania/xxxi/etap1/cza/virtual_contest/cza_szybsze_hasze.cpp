#include <bits/stdc++.h>
using namespace std;
using Hash = pair<int, int>;

constexpr int B[2] = {31, 69}, MAX_N = 1'000'005, MAX_ALPHA = 27, ILE_HASZY = 2;
constexpr int MOD[2] = {1'000'000'007, 1'000'69'69'69};

int main() {
    ios_base::sync_with_stdio(0);

    long long n, k;
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

    int pot_k[2] = {1, 1};
    int substring[2] = {0, 0};

    queue<int> q;
    // Load window.
    for (int i = 1; i <= k; i++) {
        q.push(s[i-1] - 'a' + 1);

        for (int j = 0; j < ILE_HASZY; j++) {
            pot_k[j] = 1LL * pot_k[j] * B[j] % MOD[j];
            substring[j] = (1LL * substring[j] * B[j] + s[i-1] - 'a' + 1) % MOD[j];
        }
        // cerr << substring << " " << s.substr(i-1, k) << "\n";
    }

    Hash H = {substring[0], substring[1]};
    auto forward_window = [&](char c) {
        int d = q.front();
        q.pop();
        
        for (int j = 0; j < ILE_HASZY; j++) {
            substring[j] = (1LL * substring[j] * B[j] + c - 'a' + 1) % MOD[j];
               // cerr << c << " " << d << "\n";
                substring[j] -= 1LL * d * pot_k[j] % MOD[j];
                substring[j] %= MOD[j];
                if (substring[j] < 0) substring[j] += MOD[j];
        }
        
        H = {substring[0], substring[1]};
        q.push(c - 'a' + 1);
    };

    // Move window.
    for (int i = 1; i + k <= n; i++) {
        // cerr << substring << " " << s.substr(i-1, k) << "\n";
        char c = s[i+k-1];
        occ[H][c]++;
        char best = get_best(H);
        if (occ[H][c] > occ[H][best] || (occ[H][c] == occ[H][best] && best > c)) nxt[H] = c;
        forward_window(c);
    }


    string ans;
    auto extend = [&]() -> char {
        char c = get_best(H);
        n++;
        forward_window(c);
        if (n >= a && n <= b) ans += c;
        return c;
    };

    map<Hash, int> vis;

    string predict;
    while (!vis[H]) {
        vis[H] = predict.size();
        predict += extend();
    }

    string cycle = predict.substr(vis[H]);
    long long cycle_size = cycle.size();
    cerr << cycle_size << "\n";

    // Pierwsze przejscie zebraliśmy całe.
    // Teraz trzeba tylko chodzić po cyklu.
    n += max(0LL, (a - 1 - n)) / cycle_size * cycle_size;
    // while (n + cycle_size < a) n += cycle_size;
    while (n < b) {
        extend();
    }

    cout << ans << "\n";
}