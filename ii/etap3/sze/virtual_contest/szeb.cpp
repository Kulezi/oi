#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 10005;
long double a[MAXN], b[MAXN];
int ord[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    
    vector<int> ord(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    iota(ord.begin(), ord.end(), 1);

    auto give_cost = [&](vector<int> &ord) -> double {
        double t = 0;
        for (auto i : ord) {
            t += a[i]*t + b[i];
        }
        
        return t;
    };

    vector<int> best = ord;
    do {
        cout << "[";
        for (auto i : ord) {
            cout << i << " ";
        }
        cout << "] "  << give_cost(ord) << "\n";
    } while (next_permutation(ord.begin(), ord.end()));

}