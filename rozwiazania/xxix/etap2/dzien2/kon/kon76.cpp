
// Rozwiązanie brutalne do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * h * log(h)), gdzie h to średnia głębokość wierzchołka w drzewie.
// Złożoność pamięciowa: O(n)
// Punkty: 76 (upsolve), widocznie h nie było zbyt wysokie :D

// Szkielet do rozwiązania z omówienia kon.cpp z pierwszym przyśpieszeniem.

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define cerr if(false)cerr
using namespace std;
constexpr int MAX_Q = 1'000'005;

struct Fenwick {
    int fw[MAX_Q];
    void add(int x, int delta) {
        for (; x < MAX_Q; x |= x+1) 
            fw[x] += delta;
    }
    
    int sum(int r) {
        int res = 0;
        for (; r > 0; r = (r & (r+1)) - 1)
            res += fw[r];
        return res;
    }

    int sum(int l, int r) {
	return sum(r) - sum(l-1);
    }
} jealous_add_node, picky_add_node;

int q;
pair<char, int> queries[MAX_Q];

vector<int> g[MAX_Q];
int par[MAX_Q], r[MAX_Q];
bool is_jealous[MAX_Q];

int picky_sons[MAX_Q], initial[MAX_Q], jealous_children[MAX_Q];
int son_id[MAX_Q], lson[MAX_Q], rson[MAX_Q];

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
        // ++add[v];
	jealous_add_node.add(son_id[v], 1);
        v = par[v];
    }
}

int cloned_jealous(int u) {
    int p = par[r[u]];
    if (!p) return 0;
    
    int res = 0;
    // for (auto s : g[p]) {
    //     if (r[u] < s && is_jealous[s]) res += add[s];
    res += jealous_add_node.sum(son_id[r[u]], rson[p]);

    return res;
}

void clone_picky(int v) {
    if (!par[r[v]]) return;
    //++add[r[v]];
    picky_add_node.add(son_id[r[v]], 1);
}

int cloned_picky(int u) {
    int res = 0;
    while (u != r[u]) {
        assert(is_jealous[u]);
        // for (auto s : g[par[u]]) {
        //    if (u > s && !is_jealous[s]) res += add[s];
		res += picky_add_node.sum(lson[par[u]], son_id[u]);


        u = par[u];
    }

    return res;
}

int deg(int v) {
    cerr << dbg(v) << dbg(initial[v]) << dbg(picky_sons[v]) << dbg(cloned_picky(v)) << dbg(cloned_jealous(v)) << dbg(jealous_children[v]) << endl;
    return initial[v] + picky_sons[v] + cloned_picky(v) + cloned_jealous(v) + jealous_children[v];
}

void assign_ranges(int q) {
    // Zamiast trzymać oddzielne drzewo dla każdego wierzchołka, zrobimy jedno.
    // Indeksy synów jednego typu dla jakiegoś u będą tworzyć przedział, zapamiętamy też jaki numer ma dany syn.
    int M = 0;

    for (int u = 1; u <= q; u++) {
        lson[u] = MAX_Q;
        for (auto v : g[u]) {
                son_id[v] = ++M;
            	rson[u] = M;
				lson[u] = min(lson[u], M);
		}
    } 
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

    assign_ranges(q);

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
