// Rozwiązanie do zadania 'Autostrady' z II etapu X OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + k^2)
// Złożoność pamięciowa: O(n)
// Punkty: 40 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using tup = tuple<int, int, int>;
using pii = pair<int, int>;
constexpr int MAXN = 20005;
int p[MAXN], q[MAXN];
struct S {
    set<tup> s;
    void dodaj(int i) { s.insert({i, p[i], q[i]}); }

    void usun(int i) { s.erase(s.lower_bound({i, 0, 0})); }

    int szukaj(int p, int q) {
        for (auto [i, r, s] : s) {
            if (min(p, q) >= r && max(p, q) <= s) continue;
            if ((r < p && p < s) || r < q && q < s) return i;
        }
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

    S s;
    vector<pii> pq(k);
    for (int i = 0; i < k; i++) {
        cin >> p[i] >> q[i];
        s.dodaj(i);
    }

    for (int i = 0; i < k; i++) {
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

    S polnoc, poludnie;
    for (int i = 0; i < k; i++) {
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

    
    cout << "OK\n";
    // for (int i = 0; i < k; i++) cout << (kierunek[i] < 0 ? 'N' : 'S') << "\n";
}