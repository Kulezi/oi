// Rozwiązanie do zadania 'Pionek' z I etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;

// Źródło: https://cp-algorithms.com/geometry/minkowski.html
struct pt {
    int x, y;
    pt operator+(const pt& p) const { return pt{x + p.x, y + p.y}; }
    pt operator-(const pt& p) const { return pt{x - p.x, y - p.y}; }
    long long cross(const pt& p) const { return 1LL * x * p.y - 1LL * y * p.x; }
};

// Źródło: https://cp-algorithms.com/geometry/minkowski.html
void reorder_polygon(vector<pt>& P) {
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

// Źródło: https://cp-algorithms.com/geometry/minkowski.html
vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2) {
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (cross >= 0 && i < P.size() - 2) ++i;
        if (cross <= 0 && j < Q.size() - 2) ++j;
    }
    return result;
}
constexpr int MAXN = 200005;

vector<pt> minki[MAXN];

int32_t main() {
    int n;
    cin >> n;

    vector<pt> sum = {{0, 0}};
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        minki[i] = {{0, 0}, {x, y}};
    }

    // Generujemy otoczkę wypukłą wszystkich możliwych do osiągnięcia punktów.
    // W każdej iteracji liczba niepustych zmniejsza się o połowę. 
    // Analogicznie do merge-sorta w miejscu.
    for (int i = 0; (1 << i) < n; i++) {
        bool laczyc = false;
        int ostatni_niepusty = 0;
        for (int j = 0; j < n; j++) {
            if (!minki[j].empty()) {
                if (laczyc) {
                    minki[ostatni_niepusty] = minkowski(minki[ostatni_niepusty], minki[j]);
                    minki[j].clear();
                }

                laczyc = !laczyc;
                ostatni_niepusty = j;
            }
        }
    }
    long long wynik = 0;
    for (auto i : minki[0]) wynik = max(wynik, 1LL * i.x * i.x + 1LL * i.y * i.y);

    cout << wynik << "\n";
}