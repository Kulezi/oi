#include <bits/stdc++.h>
using namespace std;

map<vector<int>, vector<int>> vis;

void ztetrisuj(vector<int> &v) {
    vector<int> nowy;
    for (auto i : v) {
        if (!nowy.empty() && i == nowy.back()) nowy.pop_back();
        else nowy.push_back(i);
    }

    v = nowy;
}

void sol(vector<int> v) {
    queue<vector<int>> q;
    q.push(v);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int i = 0; i + 1 < v.size(); i++) {
            auto tet = v;
            swap(tet[i], tet[i + 1]);
            ztetrisuj(tet);
            if (!vis.count(tet)) {
                vis[tet] = vis[v];
                vis[tet].push_back(i+1);
                q.push(tet);
            }

            if (tet.empty()) {
                cout << vis[tet].size() << "\n";
                for (auto i : vis[tet]) {
                    cout << i << "\n";
                }
                exit(0);
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> t(2 * n);
    for (auto &i : t) cin >> i;
    sol(t);
}