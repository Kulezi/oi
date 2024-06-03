#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = [" << x << "]\n"
using namespace std;

constexpr int MAXT = 1, MAXK = 2, MAXL = 5, MAXLEN = 10; 
const char* alpha = "01abcdefghijklmnopqrstuvwxyz";
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution(a, b)(rng);
}

void solve(int tc) {
    int k = R(1, MAXK);
    cout << k << "\n";

    vector<int> len(k);
    for (int i = 0; i < k; i++) {
        len[i] = R(1, MAXLEN);
        cout << len[i] << " ";
    }

    cout << "\n";

    array<string, 2> s;
    array<int, 2> true_len = {0, 0};
    for (int eq = 0; eq < 2; eq++) {
        int l = R(1, MAXL);
        cout << l << "\n";
       
        while (l--) {
            cout << alpha[R(0, 1 + k)];
        }
        cout << "\n";
    }
}

int32_t main() {
    int t = R(1, MAXT);
    cout << t << "\n";

    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
}