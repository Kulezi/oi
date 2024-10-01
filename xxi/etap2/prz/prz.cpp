// Rozwiązanie do zadania 'Przestępcy' z II etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005;

int c[MAXN], x[MAXN], y[MAXN];
int last[MAXN], prev_letter[MAXN], next_letter[MAXN];
int lborder[MAXN], rborder[MAXN];

// Dla sufiksu zaczynającego się na literce i trzyma minimalny indeks j z reszty słowa,
// że taka litera jest zarówno pod tym indeksem jak i w sufiksie.
int min_pair[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) cin >> c[i];

    int m, l;
    cin >> m >> l;
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
        prev_letter[x[i]] = x[i - 1];
    }

    for (int i = 1; i <= l; i++) cin >> y[i];
    for (int i = l; i >= 1; i--) next_letter[y[i]] = y[i - 1];

    for (int i = 1; i <= n; i++) {
        if (c[i] == x[1])
            lborder[i] = i;
        else
            lborder[i] = lborder[last[prev_letter[c[i]]]];
        last[c[i]] = i;
    }

    rborder[0] = n + 1;
    for (int i = 1; i <= k; i++) last[i] = 0;

    for (int i = n; i >= 1; i--) {
        if (c[i] == y[1])
            rborder[i] = i;
        else
            rborder[i] = rborder[last[next_letter[c[i]]]];
        last[c[i]] = i;
    }

    min_pair[n + 1] = min_pair[n + 2] = n + 1;
    for (int i = n; i >= 1; i--) {
        min_pair[i] = min_pair[i + 1];
        if (last[c[i]] < i) min_pair[i] = min(min_pair[i], last[c[i]]);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        // cerr << dbg(i) << dbg(min_pair[i]) << endl;
        if (c[i] == x[m] && min_pair[rborder[i] + 1] < lborder[i]) {
            // cerr << dbg(i) << dbg(lborder[i]) << dbg(rborder[i]) << endl;
            ans.push_back(i);
        }
    }

    cout << ans.size() << "\n";
    for (auto i : ans) cout << i << " ";
    cout << "\n";
}