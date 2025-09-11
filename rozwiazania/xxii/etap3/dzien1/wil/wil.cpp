// Rozwiązanie do zadania 'Wilcze doły'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x
using namespace std;
using ll = long long;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, d;
    ll p;
    cin >> n >> p >> d;
    vector<ll> pref(n + 1, 0);
    vector<ll> sd(n+1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    for (int i = d; i <= n; i++) sd[i] = pref[i] - pref[i-d];

    auto sum = [&](int l, int r) -> ll { return pref[r] - pref[l - 1]; };
    // Sprawdza czy można wyrównać spójny podciąg długości l.
    auto check = [&](int l) {
        // Kolejka maksimów, trzyma indeksy w których może być koniec dechy.
        // Najwięcej wycinająca decha stoi na początku.
        deque<int> dq;
        for (int koniec = d; koniec < l; koniec++) {
            while (!dq.empty() && sd[koniec] >= sd[dq.back()]) dq.pop_back();
            dq.push_back(koniec);
        }

        for (int koniec = l; koniec <= n; koniec++) {
            int poczatek = koniec - l + 1;
            ll wszystko = sum(poczatek, koniec);
            while (!dq.empty() && sd[koniec] >= sd[dq.back()]) dq.pop_back();
            dq.push_back(koniec);
            if (dq.front() < poczatek + d - 1) dq.pop_front();

            if (wszystko - sd[dq.front()] <= p) return true;
        }

        return false;
    };

    int l = d, r = n;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (check(m))
            l = m;
        else
            r = m - 1;
    }

    cout << l << "\n";
}