// Rozwiązanie do zadania 'Korale'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log^2(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
constexpr int MAXN = 200'005, N_HASHES = 2;

struct Hash {
    int n;
    vector<int> h;
    vector<int> pot;
    int MOD;
    int X;
    
    Hash() {}

    Hash(vector<int> v, int mod, int x) : n(v.size()), MOD(mod), X(x) {
        h = vector<int>(n+1, 0);
        pot = vector<int> (n+1, 1);
        for (int i = 1; i <= n; i++) {
            h[i] = (1LL * h[i-1] * X + v[i-1]) % MOD;
            pot[i] = 1LL * pot[i-1] * X % MOD;
        }
    }

    int get_hash(int l, int r) {
        int res = (h[r] - 1LL * h[l-1] * pot[r-l+1]) % MOD;
        if (res < 0) res += MOD;
        return res;
    }
};

Hash h[N_HASHES], hrev[N_HASHES];
int n;

int get_kawalek(int l, int r, int hidx) {
    return min(h[hidx].get_hash(l, r), hrev[hidx].get_hash(n - r + 1, n - l + 1));
}

pii get_kawalek(int l, int r) {
    return {get_kawalek(l, r, 0), get_kawalek(l, r, 1)};
}

int t[MAXN];


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    
    vector<int> v(n);
    for (auto &i : v) cin >> i;

    h[0] = Hash(v, 1'000'000'007, 635119);
    h[1] = Hash(v, 1'000'69'69'69, 631133);

    reverse(v.begin(), v.end());
    
    hrev[0] = Hash(v, 1'000'000'007, 635119);
    hrev[1] = Hash(v, 1'000'69'69'69, 631133);



    int max_roznych = 0;
    vector<int> jakie_k;
    for (int k = 1; k <= n; k++) {
        set<pair<int,int>> rozne;
        for (int l = 1; l + k - 1 <= n; l += k) {
            auto kawalek = get_kawalek(l, l+k-1);
            rozne.insert(kawalek);
        }

        int ile_roznych = rozne.size();
        if (ile_roznych > max_roznych) {
            max_roznych = ile_roznych;
            jakie_k = {k};
        } else if (ile_roznych == max_roznych) {
            jakie_k.push_back(k);
        }
    }

    cout << max_roznych << " " << jakie_k.size() << "\n";
    for (auto i : jakie_k) cout << i << " ";
    cout << "\n";
}