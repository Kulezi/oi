// Rozwiązanie do zadania 'Szyfr' z III etapu IX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^(n/2))
// Złożoność pamięciowa: O(2^(n/2))
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    int S;
    cin >> S;
    if (n == 1) {
        cout << (a[0] == S ? 1 : 0) << "\n";
        return 0;
    }

    int l = n / 2;
    int r = n - l;
    vector<pair<int,int>> sumy;
    for (int l_mask = 0; l_mask < (1 << l); l_mask++) {
        int sum = 0;
        for (int i = 0; i < l; i++) {
            if (l_mask >> i & 1) {
                sum += a[i];
            }
        }

        sumy.emplace_back(sum, l_mask);
    }
    sort(sumy.begin(), sumy.end());

    for (int r_mask = 0; r_mask < (1 << r); r_mask++) {
        int sum = 0;
        for (int i = 0; i < r; i++) {
            if (r_mask >> i & 1) {
                sum += a[i + l];
            }
        }

        auto it = lower_bound(sumy.begin(), sumy.end(), make_pair(S - sum, 0));
        if (it != sumy.end() && it->first == S - sum) {
            int l_mask = it->second;
            for (int i = 0; i < l; i++) cout << (l_mask >> i & 1);
            for (int i = 0; i < r; i++) cout << (r_mask >> i & 1);
            cout << "\n";
            return 0;
        }
    }
}