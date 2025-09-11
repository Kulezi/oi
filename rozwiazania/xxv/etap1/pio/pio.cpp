// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Punkty: 100

// Zamiatanie kątowe, rozważamy branie wszystkich wektorów z jednej półpłaszczyzny.
#include <bits/stdc++.h>
#define int long long
#define f first
#define s second
#define pii pair<int, int>
using namespace std;
int a, aktx, akty, b, n, p, res, N, A, B;
pii t[400005], t2[400005];
vector<pii> v;
bool comp(pii a, pii b) { return atan2l(a.f, a.s) < atan2l(b.f, b.s); }
int ilo(pii a, pii b) { return b.f * a.s - b.s * a.f; }
void fin(int &x) {
    register char c = 0;
    int minus = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    if (c == '-') minus = 1, c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
    if (minus) x = -x;
}
bool takisam(pii a, pii b) {
    bool aa = a.first < 0;
    bool bb = a.second < 0;
    bool cc = b.first < 0;
    bool dd = b.second < 0;
    if (aa == cc && bb == dd) return 1;
    return 0;
}
main() {
    ios_base::sync_with_stdio(0);
    fin(n);
    for (int i = 1; i <= n; i++) {
        fin(A);
        fin(B);
        if (A == 0 && B == 0) {
        } else
            t[++N] = {A, B};
    }
    n = N;
    N = 1;
    sort(t + 1, t + n + 1, comp);
    t2[1] = t[1];
    for (int i = 2; i <= n; i++) {
        if (atan2l(t2[N].f, t2[N].s) == atan2l(t[i].f, t[i].s) && takisam(t[i], t2[N]))
            t2[N].f += t[i].f, t2[N].s += t[i].s;
        else
            t2[++N] = t[i];
    }
    for (int i = 1; i <= N; i++) t2[i + N] = t2[i];
    for (int i = 1; i <= 2 * N; i++) {
        aktx -= t2[i - 1].f, akty -= t2[i - 1].s;
        res = max(res, aktx * aktx + akty * akty);
        while (p < min(i + N - 1, 2 * N) && ilo(t2[p + 1], t2[i]) <= 0) {
            p++, aktx += t2[p].f, akty += t2[p].s, res = max(res, aktx * aktx + akty * akty);
        }
    }
    cout << res << "\n";
}
