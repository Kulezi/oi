// Rozwiązanie brutalne do zadania 'Przekaźniki telekomunikacyjne' z II etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * |liczba aktywnych przekaźników|)
// Złożoność pamięciowa: O(n)
// Punkty: 14 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 300'000;

struct przekaznik {
    // b + a * x.
    int a, b;
};

przekaznik p[MAXN];
set<int> aktywne;

void postaw() {
    int x, s, a;
    cin >> x >> s >> a;
    p[x] = {a, s};
    aktywne.insert(x);
}

void usun() {
    int x;
    cin >> x;
    aktywne.erase(x);
}

void zapytanie() {
    int x1, x2;
    cin >> x1 >> x2;

    long long sum = 0;
    for (int x = x1; x <= x2; x++) {
        for (auto i : aktywne) {
            int d = abs(x - i);
            sum += max(0LL, p[i].b - 1LL * p[i].a * d);
        }
    }

    cout << sum / (x2 - x1 + 1) << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    while (m--) {
        string typ;
        cin >> typ;
        if (typ == "P")
            postaw();
        else if (typ == "U")
            usun();
        else if (typ == "Z")
            zapytanie();
        else
            assert(false);
    }
}