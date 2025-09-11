// Rozwiązanie do zadania 'Pakowanie plecaka'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 500'005;
int R(int l, int r) {
   static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
   return uniform_int_distribution<int>(l, r)(rng);
}

struct treap {
    ll val, delta;
    int prior;
    treap *l, *r;
    treap(ll v) : val(v), delta(0), prior(R(1, 1e18)), l(nullptr), r(nullptr) {}
    void push() { 
        if (delta == 0) return;
        if (l) l->delta += delta;
        if (r) r->delta += delta;
        val += delta;
        delta = 0;
    }
};
using ptreap = treap*;
int t[MAXN];

ll get_max(ptreap t) {
    assert(t != nullptr);
    t->push();
    if (t->r) return get_max(t->r);
    return t->val;
}

// Dodaje leniwie stałą do całego drzewa.
void add(ptreap t, int delta) { 
    if(!t) return;
    t->delta += delta; 
}

void split(ptreap t, ll v, ptreap &l, ptreap &r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    t->push();
    if (t->val <= v) {
        split(t->r, v, t->r, r);
        l = t;
    } else {
        split(t->l, v, l, t->l);
        r = t;
    }
}

void merge(ptreap &t, ptreap l, ptreap r) {
    if (!l || !r) {
        t = l ? l : r;
        return;
    } 
    l->push();
    r->push();
    if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
}

void print(ptreap t) {
    if (!t) return;
    t->push();
    if (t->l) print(t->l);
    if( t->val > 0) cout << t->val << " ";
    if (t->r) print(t->r);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    // Przyśpieszenie bruta z pliku ple38.cpp przy pomocy drzepca.
    ptreap dp = new treap(0);
    for (int i = n; i >= 1; i--) {
        ptreap l, r;
        split(dp, t[i]-1, l, r);
        ll x = get_max(l);
        ptreap m = new treap(x + t[i]);

        add(r, t[i]);
        merge(dp, l, m);
        merge(dp, dp, r);
    }

    print(dp);
    cout << "\n";
}