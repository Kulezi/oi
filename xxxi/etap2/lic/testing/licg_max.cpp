// Generatorka maxtestów.

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

constexpr int MAX_A = 10;

int32_t main() {
    srand(R(1, 999999));
    ios_base::sync_with_stdio(0);
    int n = R(1, 300000), m = R(1, 300000 / n);
    cout << n << " " << m << "\n";

    for (int i = 1; i <= n; i++) {
        // Losuj c_i.
        cout << R(1, MAX_A) << " ";
    }

    cout << "\n";
    
    vector<int> meters(n);
    for (auto &i : meters) {
        i = R(0, MAX_A);
        cout << i << " ";
    }

    cout << "\n";

    if (R(0, 1)) {
        for (int i = 1; i <= m; i++) {
            for (auto &j : meters) {
                j += R(0, MAX_A - j);
            }

            vector<int> cpy = meters;
            random_shuffle(all(cpy));
            for (auto i : cpy) cout << i << " ";
            cout << "\n";
        }
    } else {
        for (int i = 1; i <= m; i++) {
            for (auto &j : meters) {
                if (R(0, 1)) j = R(0, MAX_A);
                else j += R(0, MAX_A - j);
            }

            vector<int> cpy = meters;
            random_shuffle(all(cpy));
            for (auto i : cpy) cout << i << " ";
            cout << "\n";
        }
    }
}