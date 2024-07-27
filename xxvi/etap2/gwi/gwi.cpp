// Rozwiązanie do zadania 'Gwiazdy' z II etapu XXVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
enum {
    LEWO,
    PRAWO,
    OBOJETNIE,
};
int przeciwny(int x) {
    assert(x != OBOJETNIE);
    return 1 - x;
}
constexpr ll INF = 1'000'000'000'000;
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, s;
    cin >> n >> s;

    vector<int> l(n + 2, 0), r(n + 2, 0);
    vector<ll> pref_opt(n + 2, 0), pref_l(n + 2, 0), pref_r(n + 2, 0);
    ll sum_opt = 0;
    for (int i = 1; i <= n; i++) {
        if (i < n) cin >> l[i] >> r[i];
        pref_l[i] = pref_l[i - 1] + l[i];
        pref_r[i] = pref_r[i - 1] + r[i];
        pref_opt[i] = pref_opt[i - 1] + min(l[i], r[i]);
    }
    auto sum = [](auto &pref, int l, int r) { return pref[r] - pref[l - 1]; };

    int na_lewo = s - 1, na_prawo = n - s;
    int lewo_i = 1, prawo_i = 1;
    ll lewo_wynik = INF, prawo_wynik = INF;
    for (int i = 1; i + 1 <= n; i++) {
        // Idę i razy w lewo, a potem skręcam w prawo.
        ll res_l = pref_l[i] + r[i + 1] + sum(pref_opt, i + 2, n);
        ll res_r = pref_r[i] + l[i + 1] + sum(pref_opt, i + 2, n);
        if (i <= na_lewo && res_l < lewo_wynik) {
            lewo_wynik = res_l;
            lewo_i = i;
        }

        if (i <= na_prawo && res_r < prawo_wynik) {
            prawo_wynik = res_r;
            prawo_i = i;
        }
    }

    string ruchy;
    if (lewo_wynik < prawo_wynik) {
        cout << lewo_wynik << "\n";
        for (int i = 1; i <= lewo_i; i++) ruchy += 'L';
        if (lewo_i + 1 < n) ruchy += 'R';
        for (int i = lewo_i+2; i < n; i++) ruchy += (l[i] < r[i] ? 'L' : 'R');
    } else {
        cout << prawo_wynik << "\n";
        for (int i = 1; i <= prawo_i; i++) ruchy += 'R';
        if (prawo_i + 1 < n) ruchy += 'L';
        for (int i = prawo_i+2; i < n; i++) ruchy += (l[i] < r[i] ? 'L' : 'R');
    }

    set<int> wolne;
    for (int i = 1; i <= n; i++) wolne.insert(i);
    wolne.erase(s);
    int ostatni = s;
    cout << s;

    auto rusz = [&](int x) {
        cout << " " << x;
        wolne.erase(x);
        ostatni = x;
    };

    for (int i = 0; i < n-1; i++) {
        char ruch = ruchy[i];
        if (i == n-2) {
            cout <<  " " << *wolne.begin() << "\n";
        } else {
            if (ruchy[i] == ruchy[i+1]) {
                auto it = wolne.lower_bound(ostatni);
                if (ruch == 'L') it--;
                rusz(*it);
            } else {
                if (ruch == 'L') {
                    rusz(*wolne.begin());
                } else {
                    rusz(*(--wolne.end()));
                }
            }
        }
    }

}