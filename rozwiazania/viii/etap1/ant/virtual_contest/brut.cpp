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


int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    int best = 1, cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (d(i) > d(best)) best = i, cnt++;
    }

    cerr << cnt << "\n";
    cout << best << "\n";
}