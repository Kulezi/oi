// Rozwiązanie zadania 'Midas' z III etapu XXIV Olimpiady Informatycznej.
// Autor: Paweł Putra
// Złożoność czasowa: O(n + z).
// Złożoność pamięciowa: O(n).

#include <iostream>
#include <deque>
#include <queue>
using namespace std;
constexpr int MAXN = 2'000'005;

int l[MAXN], r[MAXN], numer[MAXN];
int ls[MAXN], rs[MAXN];
int N = 1;
int lson(int x) {
    if (!ls[x]) ls[x] = ++N;
    return ls[x];
}

int rson(int x) {
    if (!rs[x]) rs[x] = ++N;
    return rs[x];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    
    deque<int> q;
    q.push_back(1);
    numer[1] = 1;

    // Traktujemy komnaty o tym samym koszcie dojścia jako jeden wierzchołek.
    // Potem numerujemy BFSem.
    queue<int> lewe, prawe;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        
        if (l[v]) {
            if (numer[v] == numer[1]) {
                numer[l[v]] = numer[v];
                q.push_front(l[v]);
            } else { 
                lewe.push(l[v]);
            }
        }

        if (r[v]) {
            prawe.push(r[v]);
        }

        if (q.empty() || numer[q.front()] != numer[v]) {
            while (!lewe.empty()) {
                int u = lewe.front();
                numer[u] = lson(numer[v]);
                q.push_back(u);
                lewe.pop();
            }

            while (!prawe.empty()) {
                int u = prawe.front();
                numer[u] = rson(numer[v]);
                q.push_back(u);
                prawe.pop();
            }
        }
    }


    int z;
    cin >> z;
    while (z--) {
        int x, y;
        cin >> x >> y;
        cout << (numer[x] >= numer[y] ? "TAK" : "NIE") << "\n";
    }

}
