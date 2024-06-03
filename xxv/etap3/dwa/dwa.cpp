// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Punkty: 100

// Zamiatanie kątowe, rozważamy branie wszystkich wektorów z jednej półpłaszczyzny
// do jednej grupy, a z przeciwnej do drugiej.

#include <bits/stdc++.h>
#define int long long
#define ll long long
#define f first
#define s second
using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) { return atan2l(a.f, a.s) < atan2l(b.f, b.s); }
ll ilo(pair<int, int> a, pair<int, int> b) { return a.f * b.s - a.s * b.f; }
int n, N;
pair<int, int> t[1 << 20], t2[1 << 20];
ll sumx, sumy, ans, aktx, akty;
inline void getres() {
    ll iks = sumx - aktx;
    ll igreg = sumy - akty;
    ans = max(ans, (iks - aktx) * (iks - aktx) + (igreg - akty) * (igreg - akty));
}
main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i].f >> t[i].s;
        sumx += t[i].f;
        sumy += t[i].s;
    }
    sort(t + 1, t + n + 1, comp);
    for (int i = 1; i <= n; i++) {
        if (t[i].f == 0 && t[i].s == 0) continue;
        t2[++N] = t[i];
    }
    n = N;
    for (int i = 1; i <= n; i++) t[i] = t2[i];
    for (int i = n + 1; i <= n + n; i++) t[i] = t[i - n];
    aktx = t[1].f;
    akty = t[1].s;
    int l = 1;
    for (int i = 2; i <= n + n; i++) {
        aktx += t[i].f, akty += t[i].s;
        while (i - l + 1 > n || ilo(t[l], t[i]) > 0 ||
               (ilo(t[l], t[i]) == 0 && (t[l].f * t[i].f < 0 || t[l].s * t[i].s < 0))) {
            if (i == l) break;
            aktx -= t[l].f;
            akty -= t[l].s;
            l++;
            getres();
        }
        // cout << i << " " << l << endl;
        getres();
    }
    cout << ans;
}