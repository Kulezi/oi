// Generatorka testów do zadania 'Pustynia' z II etapu XXII OI.
// Autor: Paweł Putra
#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;
constexpr int MAXN = 100005;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = 1000; // od 2 bo l_i < r_i!
    int s = R(1, n);
    int m = 1000;
    cout << n << " " << s << " " << m << "\n";

    vector<int> v(n);
    iota(all(v), 1);
    random_shuffle(all(v));
    sort(v.begin(), v.begin()+s);
    for (int i = 0; i < s; i++) cout << v[i] << " " << R(1, 10) << "\n";
    cout << "\n";

    while (m--) {
        int l = R(1, n-1);
        int r = R(l+1, n);
        int k = R(1, r-l);
        cout << l << " " << r << " " << k << " ";
        vector<int> s(r-l+1);
        iota(all(s), l);
        random_shuffle(all(s));
        sort(s.begin(), s.begin()+k);
        for (int i = 0; i < k; i++) cout << s[i] << " ";
        cout << "\n";
    }

}