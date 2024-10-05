#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = " << x << "\n";
using namespace std;

constexpr int MAXK = 10, MAXN = 10005, BIN = 15;//, BIN = 1'000'000'000;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

int32_t main() {
    srand(R(1, 10000000));
    ios_base::sync_with_stdio(0);
    
    int odleglosc = R(1, 99);

    int N = odleglosc+1;
    int M = odleglosc;

    int dodatkowe_n = R(0, 100-N);
    int dodatkowe_m = R(0, 100-M);

    int n = N + dodatkowe_n;
    int m = M + dodatkowe_m;
    int d = R(odleglosc, 100);
    int k = R(1, 10);

    vector<pair<int,int>> edges;
    int stara = 1;
    for (int i = 1; i < odleglosc; i++) {
        int nowa = R(1, n-1);
        while (nowa == stara) nowa = R(1, n-1);
        edges.push_back({stara, nowa});
        stara = nowa;
    }
    edges.push_back({stara, n});

    cout << n << " " << m << " " << d << " " << k << "\n";
    for (int i = 1; i <= dodatkowe_m; i++) {
        int a = R(1, n-1);
        int b = R(a+1, n);
        edges.push_back({a, b});
    }

    for (auto [a, b] : edges) {
        cout << a << " " << b << " ";
        for (int i = 1; i <= k; i++) cout << R(0, 10) << " ";
        cout << "\n";
    }
}