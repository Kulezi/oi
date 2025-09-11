#include <bits/stdc++.h>
using namespace std;

constexpr array<int, 10> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 27};

int n;
int best = 1, d_best = 1, cnt = 1;

void b(int m, int i, int d) {
    cnt++;
    if (d > d_best || (d == d_best && best > m)) best = m, d_best = d;

    for (int j = i; j < p.size(); j++) {
        long long o = 1LL * m * p[j];
        for (int krotnosc = 1; o <= n; o *= p[j], krotnosc++) {
            b(o, j+1, d * (krotnosc+1));
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;

    b(1, 0, 1);
    cerr << cnt << "\n";
    cout << best << "\n";
}

// 2 3