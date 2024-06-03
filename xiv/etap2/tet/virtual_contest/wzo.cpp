#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;


    vector<int> vis(n+1, 0);
    vector<int> v, sol;
    for (int i = 1; i <= 2 * n; i++) {
        int x;
        cin >> x;

        if (vis[x]) {
            int pos = v.size()-1;
            while (v[pos] != x) {
                pos--;
            }
            
            while (pos != v.size()-1) {
                sol.push_back(pos+1);
                swap(v[pos], v[pos+1]);
                pos++;
            }

            v.pop_back();
        } else {
            vis[x] = i;
            v.push_back(x);
        }
    }

    cout << sol.size() << "\n";
    for (auto i : sol) cout << i << "\n";
}
