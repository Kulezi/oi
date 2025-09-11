#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005;
int L[2*MAXN], R[2*MAXN], pref[MAXN];
string s;
void zaznacz(int sum, int l, int r) {
    if (l > r) return;
    L[sum] = l+1;
    R[sum] = r+1;
    if (sum - 2 > 0) {
        if (s[l] == 'T') zaznacz(sum-2, l+1, r);
        else if(s[r] == 'T') zaznacz(sum-2, l, r-1);
        else zaznacz(sum-2, l+1, r-1);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    cin >> s;

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'T') sum += 2;
        else {
            sum++;
        }

        pref[i] = sum;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int suma = pref[i] - pref[j-1];
            L[suma] = j;
            R[suma] = i;
        }
    }


    while (m--) {
        int x;
        cin >> x;
        
        if (L[x] == 0) {
            cout << "NIE\n";
        } else {
            cout << "OK\n";

            // cout << L[x] << " " << R[x] << "\n";
        }
    }
}