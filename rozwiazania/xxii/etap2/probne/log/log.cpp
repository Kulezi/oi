// Rozwiązanie zadania 'Logistyka' z II etapu XXII OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n).
// Punkty: 100

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005;
char typ[MAXN];
int c[MAXN], ns[MAXN], a[MAXN];
vector<int> esy; // Przeskalowane s z [1, 10^9] do [1, MAXN].

struct Drzewo {
    ll suma[4*MAXN];
    int lazy[4*MAXN];
    int x, d, n;
    void dodaj(int r, int delta) {
        x = r;
        d = delta;
        _dodaj(1, 1, n-1);
    }

    ll ile(int r) {
        x = r;
        return _ile(1, 1, n-1);
    }
    
    ll len(int l, int r) {
        return esy[r] - esy[l-1];
    }

    void _dodaj(int pos, int l, int r) {
        push(pos, l, r);
        if (l > x) return;
        if (r <= x) {
            suma[pos] += len(l, r) * d;
            if (l != r) {
                lazy[pos*2] += d;
                lazy[pos*2+1] += d;
            }
            return;
        }

        int m = (l + r) / 2;
        _dodaj(pos*2, l, m);
        _dodaj(pos*2+1, m+1, r);
        suma[pos] = suma[pos*2] + suma[pos*2+1];
    }

    ll _ile(int pos, int l, int r) {
        push(pos, l, r);
        if (l > x) return 0;
        if (r <= x) {
            return suma[pos];
        }
        int m = (l + r) / 2;
        return _ile(pos*2, l, m) + _ile(pos*2+1, m+1, r);
    }

    void push(int pos, int l, int r) {
        if (lazy[pos]) {
            suma[pos] += len(l, r) * lazy[pos];
            if (l != r) {
               lazy[pos*2] += lazy[pos];
               lazy[pos*2+1] += lazy[pos];
            }
            lazy[pos] = 0;
        }
    }
} drzewo;

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) a[i] = 0;

    esy = {0};
    for (int i = 1; i <= m; i++) {
        cin >> typ[i] >> c[i] >> ns[i];
        esy.push_back(ns[i]);
    }
    
    sort(all(esy));
    esy.erase(unique(all(esy)), esy.end());

    drzewo.n = esy.size();


    for (int i = 1; i <= m; i++) {
        int s = lower_bound(all(esy), ns[i]) - esy.begin();

        if (typ[i] == 'U') {
            int osoba = c[i];
            drzewo.dodaj(a[osoba], -1);
            a[osoba] = s;
            drzewo.dodaj(a[osoba], 1);
        } else {
           cout << (drzewo.ile(s) >= 1LL * c[i] * ns[i] ? "TAK" : "NIE") << "\n";
        }
    }
}


