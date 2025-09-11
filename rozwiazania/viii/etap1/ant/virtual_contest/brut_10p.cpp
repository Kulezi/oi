#include <bits/stdc++.h>
using namespace std;

int d(int n) {
    int res = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res++;
            if (n / i != i) res++;
        }
    }
    return res;
}


constexpr array<int, 10> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 27};

int n;
int best = 1, cnt = 1;

void b(int m, int i) {
    cnt++;
    if (d(m) > d(best) || (d(m) == d(best) && best > m)) best = m;
    for (int j = i; j < p.size(); j++) {
        if (1LL * m * p[j] > n) return;
        b(m * p[j], j);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n;

    b(1, 0);
    cerr << cnt << "\n";
    cout << best << "\n";
}

// 2 3