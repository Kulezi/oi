#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 251, MAXD = MAXN * 5;

vector<int> g[MAXN];
bitset<MAXN> dasie[2][MAXD];
bitset<MAXN> ruch[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);

    int n = 250;
    cout << n << " " << n * (n-1) / 2<< "\n";
    cout << 1 << " " << 126 << "\n";
    for (int i = 1; i <= 125; i++) {
        cout << i << " " << i+1 << "\n";
    }

    cout << 125 << " " << 1 << "\n";

    for (int i = 126; i <= 248; i++) {
        cout << i << " " << i+1 << "\n";
    }

    cout << 249 << " " << 126 << "\n";
}
