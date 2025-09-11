// Rozwiązanie brutalne do zadania 'Najazd'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3*m)
// Złożoność pamięciowa: O(n)
// Punkty: 0 (upsolve)
#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define dbgp(x) #x << " = " << x.s() << " "
using namespace std;
constexpr int MAXN = 605, INF = 2'000'000'000, MAXM = 10005;
struct Punkt {
    int x, y, waga;
    string s() {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(waga) + ")";
    }
} wielokat[MAXN], fabryki[MAXM];

bool pod(Punkt a, Punkt b, Punkt p) {
    b.x -= a.x;
    p.x -= a.x;
    b.y -= a.y;
    p.y -= a.y;

    return b.x * p.y - b.y * p.x <= 0;
}

// Punkty a, b, c musza być zgodnie ze wskazówkami zegara.
bool w_trojkacie(Punkt &a, Punkt &b, Punkt &c, Punkt p) {
    return pod(a, b, p) && pod(b, c, p) && pod(c, a, p);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> wielokat[i].x >> wielokat[i].y;

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        auto &f = fabryki[i]; 
        cin >> f.x >> f.y >> f.waga;
    }

    int wynik = -INF;
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            for (int c = b + 1; c <= n; c++) {
                int sum = 0;
                for (int p = 1; p <= m; p++) {
                    if (w_trojkacie(wielokat[a], wielokat[b], wielokat[c], fabryki[p]))
                        sum += fabryki[p].waga;
                }

                if (sum > wynik) wynik = sum;
            }
        }
    }

    cout << wynik << "\n";
}