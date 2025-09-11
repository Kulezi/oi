#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005;
int L[MAXN*2], R[MAXN*2], pref[MAXN];
string s;
void zaznacz(int sum, int l, int r) {
    if (l > r) return;
    L[sum] = l;
    R[sum] = r;
    if (sum - 2 > 0) {
        if (s[l-1] == 'T') zaznacz(sum-2, l+1, r);
        else if(s[r-1] == 'T') zaznacz(sum-2, l, r-1);
        else zaznacz(sum-2, l+1, r-1);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    cin >> s;

    int sum = 0;
    int l = n+1, r = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'T') sum += 2;
        else {
            l = min(l, i);
            r = i;
            sum++;
        }

        pref[i] = sum;
    }

    zaznacz(sum, 1, n);

    if (l != n+1) {
        zaznacz(sum - pref[l], l+1, n);
        zaznacz(pref[r-1], 1, r-1);
    }

    while (m--) {
        int x;
        cin >> x;
        
        if (L[x] == 0) {
            cout << "NIE\n";
        } else {
            // cout << "OK\n";
            assert(pref[R[x]] - pref[L[x]-1] == x);
            cout << L[x] << " " << R[x] << "\n";
        }
    }
}