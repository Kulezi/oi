// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(|A| * n)
// Punkty: 100 (upsolve)

// Rozwiązanie sprowadza zadanie do |A|^2 instancji problemu podtablicy o
// największej sumie, o sumarycznej długości 2 * |A| * n, z założeniem, że ta
// podtablica musi mieć dwa rózne elementy.

// Ma dosyć dużą stałą i ledwie mieści się w limicie czasu na szkopule,
// można to poprawić przepisując logikę tak, by nie pisała nic po wektorze v,
// tylko liczyła samą tablicę sum. Nie robiłem tego, bo zależało mi bardziej na czytelności kodu. 
#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_A = 26, INF = 1'000'000'000, MAXN = 1'000'005;

int sum[MAXN];
int v[MAXN + 5];
vector<int> occ[MAX_A];

int solve_max_sum(int n) {
    int j = -1;
    int mini = INF;
    int res = 0;
    int cnt_pos = 0, cnt_neg = 0;

    for (int i = 1; i < n; i++) {
        if (v[i] > 0)
            cnt_pos++;
        else if (v[i] < 0)
            cnt_neg++;
        while (cnt_pos > 0 && cnt_neg > 0 &&
               ((cnt_pos > 1 && v[j + 1] > 0) ||
                (cnt_neg > 1 && v[j + 1] < 0) || v[j + 1] == 0)) {
            j++;
            mini = min(mini, sum[j]);
            if (v[j] > 0)
                cnt_pos--;
            else if (v[j] < 0)
                cnt_neg--;
        }

        sum[i] = sum[i - 1] + v[i];
        res = max(sum[i] - mini, res);
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    string s;
    cin >> s;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        occ[s[i] - 'a'].push_back(i);
    }

    for (int x = 0; x < MAX_A; x++) {
        for (int y = 0; y < MAX_A; y++) {
            if (x == y || occ[x].empty() || occ[y].empty()) continue;
            int n_x = static_cast<int>(occ[x].size()), n_y = static_cast<int>(occ[y].size());
            int pos_x = 0, pos_y = 0;
            v[0] = 0;
            int pos = 0;

            // Wyciągamy słowo powstałe przez usunięcie ze słowa s wszystkich liter poza literami x i y. 
            // Ta pętla przejdzie każdą literkę słowa conajwyżej 2 * |A| razy.
            while (pos_x < n_x || pos_y < n_y) {
                if (pos_x == n_x) {
                    v[++pos] = 1;
                    pos_y++;
                } else if (pos_y == n_y) {
                    v[++pos] = -1;
                    pos_x++;
                } else if (occ[y][pos_y] < occ[x][pos_x]) {
                    v[++pos] = 1;
                    pos_y++;
                } else {
                    v[++pos] = -1;
                    pos_x++;
                }
            }

            ans = max(ans, solve_max_sum(n_x + n_y + 1));
        }
    }

    cout << ans << "\n";
}