// Rozwiązanie zadania 'Kurs szybkiego czytania' z II etapu XXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * log(m))
// Złożoność pamięciowa: O(m)
// Punkty: 100 (upsolve)

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#define sz(x) (int)(x).size()
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
vector<pair<int, int>> pref;
ll n, a, b, p, m;
void dodaj(int l, int r) {
    if (l <= r) {
        pref.emplace_back(l, 1);
        pref.emplace_back(r+1, -1);
    } else {
        pref.emplace_back(0, 1);
        pref.emplace_back(r+1, -1);
        pref.emplace_back(l, 1);
    }
}

inline int MOD(ll x) {
    ll res = (x % n);
    if (res < 0) res += n;
    return res;
}

int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

ll inv(ll a) {
    int x, y;
    gcd(a, n, x, y);
    return x;
}

ll loc(ll x) {
    static ll a_inv = inv(a);
    return MOD((-b + x) * a_inv);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> a >> b >> p >> m;

    string s;
    cin >> s;

    // Wyliczam p_0 = -b / a mod n.
    ll p_0 = loc(0);

    // Wyliczam p_1 = (-b + 1) / a mod n.
    ll p_1 = loc(1);

    ll roz = llabs(p_1 - p_0);

    pref.emplace_back(0, 0);
    pref.emplace_back(n-1, 0);
    for (int k = 0; k < m; k++) {
        if (s[k] == '0') {
            int l = MOD(0 - k * a);
            int r = MOD(p - 1 - k * a);

            dodaj(l, r);
        } else {
            int l = MOD(p - k * a);
            int r = MOD(n - 1 - k * a);
            dodaj(l, r);
        }
    }
   
    // Nie chcę liczyć wystąpień cyklicznych,
    // czyli takich że pierwsza litera jest na pozycji > n-m.
    // No to po prostu sobie tam odejmę jedynkę w punkcie żeby skipnąć :)
    for (int i = n-m+1; i < n; i++) {
        int x = MOD(a*i+b);
        pref.emplace_back(x, -1);
        pref.emplace_back(x+1, 1);
    }

    vector<int> ord(pref.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [](auto lhs, auto rhs) {
        return pref[lhs].first < pref[rhs].first;
    });

    int i = 0;
    int sum = 0, last = -1;
    int wynik = 0;
    while (i < sz(pref)) {
        auto [k, v] = pref[ord[i]];
        while (i + 1 < sz(pref) && k == pref[ord[i+1]].first) {
            i++;
            v += pref[ord[i]].second;
        }

        if (sum == m) {
            wynik += k - last;
        }

        sum += v;
        last = k;
        i++;
    }

    cout << wynik << "\n";
}

