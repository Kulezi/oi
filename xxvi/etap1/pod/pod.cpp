// Autor rozwiązania: Paweł Putra (pomysł: Mieszko Grodzicki)
// Złożoność czasowa: O(jakoś mało).
// Punkty: 100 (upsolve)

// Algorytm euklidesa daje z odejmowaniem słowo z liter z {a, b}, które ma n podciągów.
// szukamy aż je znajdziemy.

#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
bool works(ll a, ll b) {
    if (__gcd(a, b) != 1) return false;
    string s;
    for (int i = 1; i <= 1001; i++) {
        if (a ==  b ) {
            cout << s << "\n";
            return true;
        } else if (a < b) {
            s += "b";
            b -= a;
        } else {
            s += "a";
            a -= b;
        }
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int q;
    cin >> q;
    while(q--) {
        cin >> n;
        ll a = max((long long)((n + 1) / (1.0 + sqrt(5)) / 2.0) - 10, 1LL);
        while (a >= 1 && !works(a, n + 1 - a)) a++;

    }
}

