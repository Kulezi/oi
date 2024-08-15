// Rozwiązanie do zadania 'Gra' z I etapu XI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define gdzie "[" << __FILE__ << ":" << __LINE__ << "] "
#define lbg(x) gdzie << dbg(x) << endl
using namespace std;

struct Grupa {
    int l, r;
    Grupa(int x) : l(x), r(x) {}
    int size() { return r - l + 1; }

    int numer = 0;
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int m, n;
    cin >> m >> n;
    vector<Grupa> grupy;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (grupy.empty() || x > grupy.back().r + 1) {
            grupy.push_back(Grupa(x));
        } else {
            grupy.back().r++;
        }
    }

    // Przypadek brzegowy: da się w jednym ruchu skończyć grę.
    if (grupy.back().r == m - 1) {
        cout << grupy.back().size() << "\n";
        return 0;
    }

    // Wyliczamy xor nieparzystych grup.
    int nimber = 0;
    for (int i = grupy.size() - 1; i >= 0; i--) {
        auto &grupa = grupy[i];
        if (i == grupy.size() - 1) {
            grupa.numer = (m - grupa.r);
        } else {
            auto &nastepna = grupy[i+1];
            grupa.numer = nastepna.numer + nastepna.l - grupa.r - 1;
        }

        if (grupa.numer % 2 == 1) nimber ^= grupa.size();
    }

    if (nimber == 0) {
        cout << "0\n";
        return 0;
    }


    int sposoby = 0;
    for (int i = 0; i < grupy.size(); i++) {
        auto &grupa = grupy[i];
        if (grupa.numer % 2 == 1) {
            int zostanie = grupa.size() ^ nimber;
            if (zostanie < grupa.size()) sposoby++;
        } else if (grupa.numer != 2) {
            int g = 0;
            if (i + 1 < grupy.size() && grupy[i+1].numer == grupa.numer - 1) {
                g = grupy[i+1].size();
            }

            // Zabieramy stary stos i dokładamy nowy.
            // x ^ g ^ (g + a) = 0
            // g + a = x ^ g
            // a = x ^ g - g
            int a = (nimber ^ g) - g;
            if (a > 0 && a <= grupa.size()) sposoby++;
        }
    }

    cout << sposoby << "\n";
}