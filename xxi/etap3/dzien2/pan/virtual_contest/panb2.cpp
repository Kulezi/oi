// Rozwiązanie brutalne do zadania 'Panele słoneczne' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * sqrt(max(s_max, w_max))^2)
// Złożoność pamięciowa: O(sqrt(max(s_max, w_max)))

#include <math.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using tup = tuple<int, int, int>;

bool dobry(int m, int x_min, int x_max) { return x_min + (m - (x_min % m)) % m <= x_max; }

vector<tup> przedzialy(int x_min, int x_max) {
    vector<tup> res;
    for (int m = 1; m <= x_max; m++) {
        if (!dobry(m, x_min, x_max)) continue;
        int ile = x_min / m;
        if (res.empty())
            res.push_back({ile, m, m});
        else {
            auto &[ile_last, l, r] = res.back();
            if (ile_last == ile && r + 1 == m) {
                r++;
            } else
                res.push_back({ile, m, m});
        }
    }

    return res;
}

void hipo(vector<tup> v) {
    assert(v.size() <= 2 * (int)sqrt(1e9) + 5);
    map<int, int> cnt;
    for (auto [w, l, r] : v) {
        cnt[w]++;
        assert(cnt[w] <= 2);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    while (n--) {
        int ans = 1;

        int s_min, s_max, w_min, w_max;
        cin >> s_min >> s_max >> w_min >> w_max;
        auto s = przedzialy(s_min, s_max);
        auto w = przedzialy(w_min, w_max);

        int i_l = 0;
        for (auto [r_c, r_min, r_max] : w) {
            while (i_l + 1 < s.size()) {
                auto [_, l_min, l_max] = s[i_l + 1];
                if (l_min <= r_max)
                    i_l++;
                else
                    break;
            }

            auto [l_c, l_min, l_max] = s[i_l];
            int m_min = max(l_min, r_min);
            int m_max = min(l_max, r_max);
            if (m_min <= m_max) ans = max(m_max, ans);
        }

        hipo(s);
        hipo(w);

        cout << ans << "\n";
    }
}