// Rozwiązanie zadania 'Podział naszyjnika' z II etapu XXII OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)

#include <iostream>
#include <list>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 1'000'000'000; // ~4*10^6
list<int> indeksy[MAXN];
int r[MAXN];

int N;
int mi[4*MAXN], najprawszy[4*MAXN], ile[4*MAXN], lazy[2*MAXN];
int lewy[MAXN], prawy[MAXN];
int ql, qr, qd;

void build() {
    for (int p = 2*N; p >= N; p--) {
        ile[p] = 1;
        najprawszy[p] = p - N;
    }

    for (int p = N; p > 0; p--) {
        ile[p] = ile[p<<1] + ile[p<<1|1];
        najprawszy[p] = najprawszy[p<<1|1];
    }
}

void pull(int p) {
    while (p > 1) {
        p >>= 1;
        mi[p] = min(mi[p<<1], mi[p<<1|1]);
        ile[p] = 0;
        if (mi[p<<1] == mi[p]) {
            ile[p] += ile[p<<1];
            najprawszy[p] = najprawszy[p<<1];
        }
        if (mi[p<<1|1] == mi[p]) {
            ile[p] += ile[p<<1|1];
            najprawszy[p] = najprawszy[p<<1|1];
        }

        mi[p] += lazy[p];
    }
}

int h;

void apply(int pos, int delta) {
    mi[pos] += delta;
    if (pos < N) lazy[pos] += delta;
}
void push(int p) {
    for (int s = h; s > 0; s--) {
        int i = p >> s;
        if (lazy[i]) {
            apply(i<<1, lazy[i]);
            apply(i<<1|1, lazy[i]);
            lazy[i] = 0;
        }
    }
}


// [l, r) !!!
void add(int l, int r, int delta) {
    l += N, r += N;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, delta);
        if (r & 1) apply(--r, delta);
    }
    pull(l0);
    pull(r0 - 1);
}

int res_ile, res_najprawszy;
void query(int l, int r) {
    res_ile = 0;
    res_najprawszy = 0;
    l += N, r += N;
    push(l);
    push(r-1);
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (mi[l] == 0) {
                res_ile += ile[l];
                res_najprawszy = max(res_najprawszy, najprawszy[l]);
            }
            l++;
        }

        if (r & 1) {
            r--;
            if (mi[r] == 0) {
                res_ile += ile[r];
                res_najprawszy = max(res_najprawszy, najprawszy[r]);
            }
        }
    }
}

void put(int i, int delta) {
    if (indeksy[i].size() == 1) return;
    add(indeksy[i].front(), indeksy[i].back(), delta);
}

// Szybkie wczytywanie bo na szkopule były ustawione strasznie ciasne limity.
void fin(int &x) {
    x = 0;
    register char c = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}

int32_t main() {
    int n, k;
    fin(n); fin(k);
    for (int i = 1; i <= n; i++) {
        fin(r[i]);
        indeksy[r[i]].push_back(i);
    }



    N = 2*n+1;
    while ((1 << (h+1)) <= N) h++;
    build();

    for (int i = 1; i <= k; i++) put(i, 1);

    long long sposoby = 0;
    int min_roznica = n-1;

    // Wybieramy gdzie będzie się zaczynała krótsza część.
    for (int i = 1; i <= n; i++) {
        // Weź wynik (ile, najprawszy) z zapytania.
        // Koniec krótszej części może być najdalej w i + n/2
        query(i, i + n / 2);

        if (res_ile > 0) {
            sposoby += res_ile;
            int l_krotszy = res_najprawszy - i + 1;
            int roznica = (n - l_krotszy) - l_krotszy;
            min_roznica = min(min_roznica, roznica);
            
            // Kawałki o równej długości policzyliśmy dwukrotnie.
            if (roznica == 0 && i > n / 2) sposoby--;
        }
        // Usuń przedział, który wypada.
        int c = r[i];
        put(c, -1);
        
        // Dodaj ten co wpada.
        indeksy[c].push_back(indeksy[c].front() + n);
        indeksy[c].pop_front();
        put(c, 1); 
    }

    

    cout << sposoby << " " << min_roznica << "\n";
}

