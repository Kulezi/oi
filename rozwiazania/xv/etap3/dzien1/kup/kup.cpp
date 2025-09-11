// Rozwiązanie do zadania 'Kupno gruntu' z III etapu XV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MAXN = 2005;

ll dp[MAXN][MAXN];
int ban[MAXN][MAXN];
int sum(int lgx, int lgy, int pdx, int pdy) {
    return dp[pdx][pdy] - dp[lgx - 1][pdy] - dp[pdx][lgy - 1] + dp[lgx - 1][lgy - 1];
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int k, n;
    cin >> k >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + x;
            if (x > 2 * k) {
                ban[i][j] = i;
            } else {
                ban[i][j] = ban[i - 1][j];
            }
        }
    }

    auto rect_with_sum_at_least_k = [&]() -> tuple<int, int, int, int> {
        for (int i = 1; i <= n; i++) {
            vector<pii> bans;
            ban[i][n + 1] = i;
            for (int j = 1; j <= n + 1; j++) {
                int cur_ban = ban[i][j] + 1;
                int cur_lgy = j;

                while (!bans.empty() && bans.back().first < cur_ban) {
                    auto [lgx, lgy] = bans.back();
                    int pdx = i;
                    int pdy = j - 1;
                    if (sum(lgx, lgy, pdx, pdy) >= k) return {lgx, lgy, pdx, pdy};

                    cur_lgy = lgy;
                    bans.pop_back();
                }

                if (cur_ban <= i && (bans.empty() || cur_ban < bans.back().first))
                    bans.emplace_back(cur_ban, cur_lgy);
            }
        }

        return {0, 0, 0, 0};
    };

    auto [lgx, lgy, pdx, pdy] = rect_with_sum_at_least_k();
    if (lgx == 0 || sum(lgx, lgy, pdx, pdy) < k) {
        cout << "NIE\n";
        return 0;
    }

    while (sum(lgx, lgy, pdx, pdy) > 2 * k) {
        int mid_x = (lgx + pdx) / 2;
        int mid_y = (lgy + pdy) / 2;
        if (lgx < pdx && sum(lgx, lgy, mid_x, pdy) >= k)
            pdx = mid_x;
        else if (lgx < pdx && sum(mid_x + 1, lgy, pdx, pdy) >= k)
            lgx = mid_x + 1;
        else if (sum(lgx, lgy, pdx, mid_y) >= k)
            pdy = mid_y;
        else
            lgy = mid_y + 1;
    }

    assert(sum(lgx, lgy, pdx, pdy) >= k);
    cout << lgy << " " << lgx << " " << pdy << " " << pdx << "\n";
}