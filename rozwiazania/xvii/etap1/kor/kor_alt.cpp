// Rozwiązanie do zadania 'Korale' z I etapu XVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log^2(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using pii = pair<int, int>;
template <typename T>
vector<int> scale(vector<T> &v) {
    int n = v.size();
    vector<pair<T, int>> scale(n);
    vector<int> res(n);
    for (int i = 0; i < n; i++) scale[i] = {v[i], i};
    sort(all(scale));

    T last = scale[0].first;
    int m = 0;
    for (auto [val, idx] : scale) {
        if (last != val) m++;
        res[idx] = m;

        last = val;
    }

    return res;
}

// Słownik podsłów bazowych.
struct Id {
    int n;
    int max_k;
    vector<vector<int>> id;

    Id() {}

    Id(vector<int> v) : n(v.size()), max_k(0), id{scale(v)} {
        int pot2 = 1;
        while (pot2 * 2 <= n) {
            int sz = n - pot2 * 2 + 1;
            vector<pii> pary(sz);
            for (int i = 0; i < sz; i++) {
                pary[i] = {id.back()[i], id.back()[i + pot2]};
            }

            id.push_back(scale(pary));
            max_k++;
            pot2 *= 2;
        }
    }

    pii get(int l, int r) {
        int m = r - l + 1;
        int k = 0, pot2 = 1;
        while (pot2 * 2 <= m) {
            k++;
            pot2 *= 2;
        }

        return {id[k][l], id[k][r - pot2 + 1]};
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &i : v) cin >> i;
    for (int i = n - 1; i >= 0; i--) v.push_back(v[i]);
    Id slownik(v);
    reverse(all(v));

    int max_roznych = 0;
    vector<int> jakie_k;
    for (int k = 1; k <= n; k++) {
        set<pii> rozne;
        for (int l = 0; l + k - 1 < n; l += k) {
            int r = l + k - 1;
            auto a = slownik.get(l, r);
            auto b = slownik.get(n + n - 1 - r, n + n - 1 - l);
            // Żeby utożsamić s z odwróconym s bierzemy mniejszy z ich identyfikatorów.
            rozne.insert(min(a, b));
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