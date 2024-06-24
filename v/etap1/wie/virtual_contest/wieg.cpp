#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
constexpr int MAXN = 1000;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

// Wybiera losowy trójkąt z wielokąta jako część triangulacji i rekurencyjnie
// trianguluje do 3 pozostałych wielokątów.
void triangulate(vector<int> v) {
    if (v.size() <= 2) return;

    random_shuffle(all(v));
    int a = v[0], b = v[1], c = v[2];
    cout << a << " " << b << " " << c << "\n";
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    sort(all(v));

    vector<int> v1, v2, v3;
    for (auto i : v) {
        if (i >= a && i <= b) v1.push_back(i);
        if (i >= b && i <= c) v2.push_back(i);
        if (i <= a || i >= c) v3.push_back(i);
    }

    triangulate(v1);
    triangulate(v2);
    triangulate(v3);
}

int32_t main() {
    srand(R(1, 1'000'000'000));
    int n = R(3, MAXN);
    cout << n << endl;

    vector<int> vertices(n);
    iota(all(vertices), 0);
    triangulate(vertices);
}