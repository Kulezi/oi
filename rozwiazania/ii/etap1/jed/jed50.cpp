// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(t * n^2).
// Punkty: 50  (100 ja 

#include <bits/stdc++.h>
using namespace std;

void solve(int tc) {
    int n;
    cin >> n;

    queue<pair<string, int>> q;
    q.push({"", 0});
    vector<int> vis(n, 0);
    while (!q.empty()) {
        string s = q.front().first;
        int reszta = q.front().second;
        q.pop();
        if (reszta == 0 && !s.empty()) {
            cout << s << "\n";
            return;
        }

        int reszta_0 = (reszta * 10) % n;
        int reszta_1 = (reszta * 10 + 1) % n;
        if (s != "" && !vis[reszta_0]) {
            vis[reszta_0] = 1;
            q.push({s + "0", reszta_0});
        }

        if (!vis[reszta_1]) {
            vis[reszta_1] = 1;
            q.push({s + "1", reszta_1});
        }
    }

    cout << "BRAK\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int tests;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        solve(tc);
    }
}
