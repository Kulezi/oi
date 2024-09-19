#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    int n, x;
    cin >> n;
    vector<string> s(n);
    for (auto &i : s) cin >> x >>  i;

    int res = 0;
    for (auto a : s)
        for (auto b : s) {
            string w = a + b;
            string rev = w;
            reverse(rev.begin(), rev.end());
            if (rev == w) res++;
        }

    cerr << res << endl;
    cout << res << "\n";
}