// Rozwiązanie do zadania 'Zosia' z III etapu XIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((2^(n-k) + k) * (n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve), dosyć wolne, na conteście pewnie by nie weszło na 100.
// Słabą stałą da się poprawić wyrzucając wierzhołki o wysokim stopniu bez seta.

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005;
int n, k;

set<int> wynikowy = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, wyrzucone;

int zablokowany[MAXN];
vector<int> g[MAXN];

int degs[MAXN];
set<pair<int, int>> s;
void change(int v, int delta) {
    if (degs[v] > 0) s.erase({degs[v], v});
    degs[v] += delta;
    if (degs[v] > 0) s.insert({degs[v], v});
}

pair<int, int> max_deg_vertex() { return *--s.end(); }
void zablokuj(int v) {
    assert(!zablokowany[v]);
    zablokowany[v] = 1;
    change(v, -degs[v]);
    for (auto u : g[v]) {
        if (!zablokowany[u]) change(u, -1);
    }
}

void odblokuj(int v) {
    assert(zablokowany[v]);
    int deg = 0;
    for (auto u : g[v]) {
        if (!zablokowany[u]) {
            change(u, 1);
            deg++;
        }
    }
    zablokowany[v] = 0;
    change(v, deg);
}

// Znajduje wszystkie zbiory niezależne.
// k - liczba wierzchołków, które jeszcze mogę usunąć.
void find_iset(int k) {
    auto [deg, v] = max_deg_vertex();
    if (deg == 0) {
        if (wyrzucone.size() < wynikowy.size()) wynikowy = wyrzucone;
        return;
    }

    if (k == 0) return;

    // Nie biorę wierzchołka v do IS.
    zablokuj(v);
    wyrzucone.insert(v);

    find_iset(k - 1);

    wyrzucone.erase(v);
    odblokuj(v);

    // Biorę v do IS.
    if (deg <= k) {
        // Jak on pójdzie na imprezę to wszyscy sąsiedzi nie mogą.
        zablokuj(v);
        vector<int> do_odblokowania;

        int nk = k;
        for (auto u : g[v]) {
            if (!zablokowany[u]) {
                zablokuj(u);

                do_odblokowania.push_back(u);
                nk--;
                wyrzucone.insert(u);
            }
        }

        assert(nk < k);
        find_iset(nk);

        reverse(do_odblokowania.begin(), do_odblokowania.end());
        for (auto u : do_odblokowania) {
            odblokuj(u);
            wyrzucone.erase(u);
        }
        odblokuj(v);
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

    k = n - k;

    vector<int> interesting;
    for (auto [a, b] : v) {
        g[a].push_back(b);
        g[b].push_back(a);
        degs[a]++;
        degs[b]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degs[i]) interesting.push_back(i);
    }

    s.insert({0, 0});
    for (auto i : interesting) s.insert({degs[i], i});

    find_iset(k);

    if (wynikowy == BRAK_WYNIKU)
        cout << "NIE\n";
    else {
        cout << n - wynikowy.size() << "\n";
        for (auto i : wynikowy) nie_idzie[i] = true;
        for (int i = 1; i <= n; i++) {
            if (!nie_idzie[i]) cout << i << " ";
        }

        cout << "\n";
    }
}