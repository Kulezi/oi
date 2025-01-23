#include <bits/stdc++.h>
using namespace std;

// Źródło: https://cp-algorithms.com/geometry/minkowski.html
struct pt {
    long long x, y;
    pt operator+(const pt& p) const { return pt{x + p.x, y + p.y}; }
    pt operator-(const pt& p) const { return pt{x - p.x, y - p.y}; }
    long long cross(const pt& p) const { return x * p.y - y * p.x; }
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

int32_t main() {
    int n;
    cin >> n;

    vector<pt> sum = {{0, 0}};
    while (n--) {
        int x, y;
        cin >> x >> y;
        sum = minkowski(sum, {{0, 0}, {x, y}});
    }

    // Generujemy otoczkę wypukłą wszystkich możliwych do osiągnięcia punktów.
    long long res = 0;
    for (auto i : sum) {
        res = max(res, i.x * i.x + i.y * i.y);
    }

    cout << res << "\n";
}