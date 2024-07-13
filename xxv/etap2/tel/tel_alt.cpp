// Rozwiązanie do zadania 'Przekaźniki telekomunikacyjne' z II etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
constexpr int MAXN = 300'005;

struct przekaznik {
    int a, s, x;
};

przekaznik p[MAXN];

struct Wezel {
    ll a = 0, b = 0, sum = 0;
};

ll suma_ciagu(ll a, ll r, ll n) { return (a + a + (n - 1) * r) * n / 2; }

int n;
struct Drzewo {
#define ja t[pos]
#define lewy t[pos * 2]
#define prawy t[pos * 2 + 1]
    vector<Wezel> t;
    Drzewo() : t(4 * (n + 1)) {}

    void propaguj(int pos, int l, int r) {
        int m = (l + r) / 2;
        ja.sum += suma_ciagu(ja.b, ja.a, r-l+1);
        if (l != r) {
            lewy.a += ja.a;
            prawy.a += ja.a;
            lewy.b += ja.b;
            prawy.b += 1LL * (m - l + 1) * ja.a + ja.b;
        }

        ja.a = ja.b = 0;
    }

    void dodaj(int ql, int qr, int a, ll b, int pos = 1, int l = 1, int r = n) {
        propaguj(pos, l, r);
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            ja.a += a;
            ja.b += b;
            propaguj(pos, l, r);
            return;
        }

        int m = (l + r) / 2;
        dodaj(ql, qr, a, b, pos * 2, l, m);
        dodaj(ql, qr, a, b + 1LL * (m - l + 1) * a, pos * 2 + 1, m + 1, r);
        ja.sum = lewy.sum + prawy.sum;
    }

    ll pytaj(int ql, int qr, int pos = 1, int l = 1, int r = n) {
        propaguj(pos, l, r);
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) {
            return ja.sum;
        }

        int m = (l + r) / 2;
        return pytaj(ql, qr, pos * 2, l, m) + pytaj(ql, qr, pos * 2 + 1, m + 1, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int m;
    cin >> n >> m;
    Drzewo drzewo;

    auto wlicz = [&](przekaznik p, int mnoznik) {
        int max_d = p.s / p.a;
        int l = max(1, p.x - max_d);
        int r = min(n, p.x + max_d);
        // Ciąg arytmetyczny na lewo od przekaźnika.
        if (l < p.x) {
            ll b = p.s - 1LL * (p.x - 1) * p.a;
            int a = p.a;
            a *= mnoznik;
            b *= mnoznik;
            drzewo.dodaj(l, p.x - 1, a, b);
        }

        // Ciąg arytmetyczny na prawo od przekaźnika włącznie z nim.
        ll b = p.s + 1LL * (p.x - 1) * p.a;
        int a = -p.a;
        a *= mnoznik;
        b *= mnoznik;
        drzewo.dodaj(p.x, r, a, b);
    };

    auto postaw = [&]() {
        int x, s, a;
        cin >> x >> s >> a;
        p[x] = {a, s, x};
        wlicz(p[x], 1);
    };

    auto usun = [&]() {
        int x;
        cin >> x;
        wlicz(p[x], -1);
    };

    auto zapytanie = [&]() {
        int x1, x2;
        cin >> x1 >> x2;
        cout << drzewo.pytaj(x1, x2) / (x2 - x1 + 1) << "\n";
    };

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