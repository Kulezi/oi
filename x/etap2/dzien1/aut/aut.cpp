// Rozwiązanie do zadania 'Autostrady' z II etapu X OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + k * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
constexpr int MAXN = 20005, INF = 2 * MAXN;
constexpr pii MINI = make_pair(-INF, -1), MAXI = make_pair(INF, -1);
int p[MAXN], q[MAXN];
int base = 1;
struct S {
    int n, base = 1;
    vector<set<pii>> konce, poczatki;
    vector<pii> mx, mi;
    S(int N) : n(N), konce(n+1), poczatki(n+1) {
        while (base <= n) base *= 2;
        mx = vector<pii>(2 * base, MINI);
        mi = vector<pii>(2*base, MAXI);
    }

    void update(int i) {
        auto koniec = (konce[i].empty() ? MINI : *(--konce[i].end()));
        auto poczatek = (poczatki[i].empty() ? MAXI : *poczatki[i].begin());

        i += base;
        mx[i] = koniec;
        mi[i] = poczatek;
        while (i > 1) {
            i /= 2;
            mx[i] = max(mx[i*2], mx[i*2+1]);
            mi[i] = min(mi[i*2], mi[i*2+1]);
        }
    }

    void dodaj(int i) {
        konce[p[i]].insert({q[i], i});
        poczatki[q[i]].insert({p[i], i});
        update(p[i]);
        update(q[i]);
    }

    void usun(int i) {
        konce[p[i]].erase({q[i], i});
        poczatki[q[i]].erase({p[i], i});
        
        update(p[i]);
        update(q[i]);
    }

    pii query(int l, int r) {
        if (l > r) return {-1, -1};
        l += base;
        r += base;
        
        pii res_mi = min(mi[l], mi[r]), res_mx = max(mx[l],mx[r]);
        while (l / 2 != r / 2) {
            if (l % 2 == 0) {
                res_mi = min(res_mi, mi[l+1]);
                res_mx = max(res_mx, mx[l+1]);
            }

            if (r % 2 == 1) {
                res_mi = min(res_mi, mi[r-1]);
                res_mx = max(res_mx, mx[r-1]);
            }

            l /= 2;
            r /= 2;
        }

        return {res_mi.second, res_mx.second};
    }

    int szukaj(int l, int r) {
        auto [min_w_lewo, max_w_prawo] = query(l+1, r-1);  
        if (min_w_lewo != -1 && p[min_w_lewo] < l) return min_w_lewo;
        if (max_w_prawo != -1 && q[max_w_prawo] > r) return max_w_prawo;

        return -1;
    }
};

void nie() {
    cout << "NIE\n";
    exit(0);
}

char kierunek[MAXN];
int32_t main() {
    int n, k;
    cin >> n >> k;
    S s(n);
    for (int i = 1; i <= k; i++) {
        cin >> p[i] >> q[i];
        s.dodaj(i);
    }

    for (int i = 1; i <= k; i++) {
        if (kierunek[i]) continue;
        queue<int> Q;
        s.usun(i);
        Q.push(i);
        kierunek[i] = 1;
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int u = s.szukaj(p[v], q[v]); u != -1; u = s.szukaj(p[v], q[v])) {
                kierunek[u] = -kierunek[v];
                Q.push(u);
                s.usun(u);
            }
        }
    }

    S polnoc(n), poludnie(n);
    for (int i = 1; i <= k; i++) {
        if (kierunek[i] < 0) {
            if (polnoc.szukaj(p[i], q[i]) != -1) {
                nie();
            }
            polnoc.dodaj(i);
        } else {
            if (poludnie.szukaj(p[i], q[i]) != -1) {
                nie();
            }
            poludnie.dodaj(i);
        }
    }

    for (int i = 1; i <= k; i++) cout << (kierunek[i] < 0 ? 'N' : 'S') << "\n";
}