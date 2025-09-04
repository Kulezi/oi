// Rozwiązanie brutalne do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * h^2) gdzie h to *średnia* głębokość wierzchołka :)
// Złożoność pamięciowa: O(n)
// Punkty: 30 (upsolve), widocznie testy drugiego podzadania nie miały w sobie ścieżek :D

// Szkielet do rozwiązania z omówienia kon.cpp bez żadnych z przyśpieszeń.

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define cerr if(false)cerr
using namespace std;
constexpr int MAX_Q = 1'000'005;
int q;
pair<char, int> queries[MAX_Q];

vector<int> g[MAX_Q];
int par[MAX_Q], r[MAX_Q];
bool is_jealous[MAX_Q];

int add[MAX_Q], picky_sons[MAX_Q], initial[MAX_Q], jealous_children[MAX_Q];

void add_edge(int src, int dst, char typ) {
    g[src].push_back(dst);
    par[dst] = src;
    r[dst] = dst;
    if (typ == 'Z') {
        r[dst] = r[src];
        is_jealous[dst] = true;
    }
    // Tu chyba numer będzie jeszcze wygodnie ustawić, ale nie wiem czy bedzie potrzebny.
}

void clone_jealous(int v) {
    while (v != r[v]) {
        ++add[v];
        v = par[v];
    }
}

int cloned_jealous(int u) {
    int p = par[r[u]];
    if (!p) return 0;
    
    int res = 0;
    for (auto s : g[p]) {
        cerr << dbg(u) << dbg(r[u]) << dbg(s) <<  dbg(add[s]) <<  endl;
        if (r[u] < s && is_jealous[s]) res += add[s];
    }

    return res;
}

void clone_picky(int v) {
    if (!par[r[v]]) return;
    ++add[r[v]];
}

int cloned_picky(int u) {
    int res = 0;
    while (u != r[u]) {
        assert(is_jealous[u]);
        for (auto s : g[par[u]]) {
            if (u > s && !is_jealous[s]) res += add[s];
        }

        u = par[u];
    }

    return res;
}

int deg(int v) {
    cerr << dbg(v) << dbg(initial[v]) << dbg(picky_sons[v]) << dbg(cloned_picky(v)) << dbg(cloned_jealous(v)) << dbg(jealous_children[v]) << endl;
    return initial[v] + picky_sons[v] + cloned_picky(v) + cloned_jealous(v) + jealous_children[v];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> q;

    r[1] = 1;
    add_edge(1, 2, 'W');
    for (int i = 1, t = 2; i <= q; i++) {
        auto &[typ, v] = queries[i];
        cin >> typ >> v;

        if (typ == 'W' || typ == 'Z') {
            ++t;
            add_edge(v, t, typ);
        } else { 
            assert(typ == '?');
        }
    }

    queries[0] = {'W', 1};
    for (int i = 0, t = 1; i <= q; i++) {
        auto &[typ, v] = queries[i];
        if (typ == 'W') {
            ++t;
            ++picky_sons[v];
            initial[t] = 1 - deg(t);
        } else if (typ == 'Z') {
            t++;
            initial[t] = deg(v) - deg(t);
            clone_jealous(t);
            clone_picky(t);
            jealous_children[par[r[v]]]++;
        } else {
            assert(typ == '?');
            cout << deg(v) << endl;
        }
    }

}
