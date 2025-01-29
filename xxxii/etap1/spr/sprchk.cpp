// Czekerka do zadania 'Sprawiedliwy podział' z I Etapu XXXII OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 500005, INF = 2'000'000'000;
int n;
int a[MAXN], b[MAXN];

// ./sprchk []
int32_t main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "usage: ./sprchk <test.in> <sol.out>\n";
        return 1;
    }

    ifstream test(argv[1]);
    ifstream sol(argv[2]);

    int n;
    test >> n;
    assert(n >= 1 && n <= 500'000);
    for (int i = 0; i < n; i++) {
        test >> a[i];
        assert(a[i] >= 1 && a[i] <= 1'000'000'000);
    }

    for (int i = 0; i < n; i++) {
        test >> b[i];
        assert(b[i] >= 1 && b[i] <= 1'000'000'000);
    }

    ll sum_a = 0, sum_b = 0;
    int min_a = INF, min_b = INF;
    for (int i = 0; i < n; i++) {
        int x;
        sol >> x;
        if (x == 1) {
            // Ten przedmiot trafia do Bitka.
            sum_a -= a[i];
            sum_b += b[i];
            min_a = min(min_a, a[i]);
        } else {
            sum_a += a[i];
            sum_b -= b[i];
            min_b = min(min_b, b[i]);
        }
    }

    int exit_code = 0;
    if (sum_a + min_a < 0) {
        cout << dbg(sum_a + min_a) << " < 0 !\n";
        exit_code = 1;
    }

    if (sum_b + min_b < 0) {
        cout << dbg(sum_b + min_b) << " < 0 !\n";
        exit_code = 1;
    }

    return exit_code;
}
