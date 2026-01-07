// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(t * n).
// Punkty: 100 (upsolve).

#include <bits/stdc++.h>
using namespace std;

void solve(int tc) {
    int n;
    cin >> n;

    queue<int> q;
    q.push(0);
    vector<int> skad(n, 0), vis(n, 0);
    vector<char> cyfra(n, 0);
    while (!q.empty()) {
        int reszta = q.front();
        q.pop();
        if (reszta == 0 && vis[reszta]) {
            string s;
            do {
                s += cyfra[reszta];
                reszta = skad[reszta];
            } while (reszta != 0);

            reverse(s.begin(), s.end());
            cout << s << "\n";
            return;
        }

        int reszta_0 = (reszta * 10) % n;
        int reszta_1 = (reszta * 10 + 1) % n;
        if (reszta != 0 && !vis[reszta_0]) {
            vis[reszta_0] = 1;
            skad[reszta_0] = reszta;
            cyfra[reszta_0] = '0';
            q.push(reszta_0);
        }

        if (!vis[reszta_1]) {
            vis[reszta_1] = 1;
            skad[reszta_1] = reszta;
            cyfra[reszta_1] = '1';
            q.push(reszta_1);
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
