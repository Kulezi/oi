// Rozwiązanie wolne do zadania 'Zosia' z III etapu XIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(2^(n-k) * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 80 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005;
int n, k;

set<int> wynikowy = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, wyrzucone;

int zablokowany[MAXN];
vector<int> g[MAXN];

pair<int, int> max_deg_vertex() {
    int res = -1, max_deg = -1;
    for (int v = 1; v <= n; v++) {
        if (zablokowany[v]) continue;
        int deg = 0;
        for (auto u : g[v])
            if (!zablokowany[u]) deg++;
        if (deg > max_deg) {
            res = v;
            max_deg = deg;
        }
    }

    return {res, max_deg};
}

void find_iset(int k) {
    auto [v, deg] = max_deg_vertex();
    if (v == -1 || deg == 0) {
        if (wyrzucone.size() < wynikowy.size()) wynikowy = wyrzucone;
        return;
    }

    if (k == 0) return;

    assert(!zablokowany[v]);
    // Nie biorę wierzchołka v do IS.
    zablokowany[v] = 1;
    wyrzucone.insert(v);
    find_iset(k - 1);
    zablokowany[v] = 0;
    wyrzucone.erase(v);
    // Biorę v do IS.
    if (deg <= k) {
        // Jak on pójdzie na imprezę to wszyscy sąsiedzi nie mogą.
        zablokowany[v] = 1;
        vector<int> odblokuj;

        int nk = k;
        for (auto u : g[v]) {
            if (!zablokowany[u]) {
                zablokowany[u] = 1;
                odblokuj.push_back(u);
                nk--;
                wyrzucone.insert(u);
            }
        }

        assert(nk < k);
        find_iset(nk);

        for (auto i : odblokuj) {
            zablokowany[i] = 0;
            wyrzucone.erase(i);
        }
        zablokowany[v] = 0;
    }
}

set<int> BRAK_WYNIKU = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int nie_idzie[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;

    int m;
    cin >> m;

    vector<pair<int, int>> v;
    while (m--) {
        int a, b;
        cin >> a >> b;

        v.push_back({min(a, b), max(a, b)});
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (auto [a, b] : v) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    find_iset(n - k);

    if (wynikowy == BRAK_WYNIKU)
        cout << "NIE\n";
    else {
        cout << n - wynikowy.size() << "\n";
        for (auto i : wynikowy) nie_idzie[i] = true;
        // for (int i = 1; i <= n; i++) {
        //     if (!nie_idzie[i]) cout << i << " ";
        // }

        cout << "\n";
    }
}