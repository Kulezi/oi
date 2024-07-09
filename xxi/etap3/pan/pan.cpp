// Rozwiązanie do zadania 'Panele słoneczne' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * sqrt(max(s_max, w_max)))
// Złożoność pamięciowa: O(1)

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
using tup = tuple<int, int, int>;

bool dobry(int m, int x_min, int x_max) {
    int d = x_min / m;

    // Dla ustalonego ile to tylko rośnie przy rosnącym m.
    // Przypadek brzegowy to największe m dla danego d, wtedy m może być równe 0.
    int brakuje = (d + 1) * m;
    if (x_min % m == 0) brakuje = 0;

    return brakuje <= x_max;
}

vector<tup> przedzialy(int x_min, int x_max) {
    vector<tup> res;

    // x_min / m >= sqrt(n) tylko dla m <= sqrt(m).
    int ile;
    for (int m = 1; m * m <= x_min; m++) {
        ile = x_min / m;
        if (!dobry(m, x_min, x_max)) continue;

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

    // Jak d = x / m <= sqrt(n) to musi zachodzić.
    // Dobre m dla danego d tworzą maksymalnie dwa przedziały, które znajdujemy w O(1).
    // Muszą być zawarte w [lo, hi]

    for (int d = ile - 1; d >= 0; d--) {
        // Dzielenie musi dawać wynik conajmniej d.
        // x >= d * lo
        // lo <= x / d
        int lo = x_min / (d + 1) + 1;

        // Dzielenie musi dawać mniejszy wynik niż d+1.
        // x <= (d + 1) * hi
        // x / (d+1) <= hi
        // hi >= x / (d + 1)
        int hi = (d == 0 ? x_max : x_min / d);
        if (lo > hi) continue;

        int kon = x_max / (d + 1);
        if (dobry(lo, x_min, x_max)) {
            res.push_back({d, lo, kon});
        }

        if (kon != hi && dobry(hi, x_min, x_max)) {
            res.push_back({d, hi, hi});
        }
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    while (n--) {
        int ans = 1;

        int s_min, s_max, w_min, w_max;
        cin >> s_min >> s_max >> w_min >> w_max;

        // Wyznaczamy przedziały dobrych długości boku oddzielnie dla każdego z wymiarów.
        auto s = przedzialy(s_min, s_max);
        auto w = przedzialy(w_min, w_max);

        // Dla każdego przedziału dobrych wysokości
        // szukamy największej dobrej szerokości zawartej w nim gąsienicą.
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

        cout << ans << "\n";
    }
}