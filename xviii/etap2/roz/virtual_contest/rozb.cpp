#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_A = 26;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    string s;
    cin >> s;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        vector<int> cnt(MAX_A, 0);
        for (int j = i; j < n; j++) {
            int c = s[j] - 'a';
            cnt[c]++;

            int mi = n;
            int mx = 0;
            for (int m = 0; m < MAX_A; m++) {
                if (cnt[m] == 0) continue;
                mi = min(mi, cnt[m]);
                mx = max(mx, cnt[m]);
            }

            ans = max(ans, abs(mi - mx));
        }
    }

    cout << ans << "\n";
}