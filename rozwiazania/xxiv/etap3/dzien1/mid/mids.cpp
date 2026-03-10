// Rozwiązanie powolne zadania 'Midas' z III etapu XXIV Olimpiady Informatycznej.
// Autor: Paweł Putra
// Złożoność czasowa: O(n + z).
// Złożoność pamięciowa: O(n).

#include <iostream>
#include <deque>
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
    numer[1] = 0;

    // Traktujemy komnaty o koszcie dojścia 0 jako jeden wierzchołek,
    // numerujemy komnaty w kolejności odwiedzania bfsem.
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        
        if (l[v]) {
            numer[l[v]] = 2 * numer[v];
            if (numer[v] == numer[1]) {
                q.push_front(l[v]);
            } else { 
                q.push_back(l[v]);
            }
        }

        if (r[v]) {
            numer[r[v]] = 2 * numer[v] + 1;
            q.push_back(r[v]);
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
