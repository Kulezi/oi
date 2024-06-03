// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*log(n))
// Punkty: 100 (upsolve)

// Bierze do tomiku zawsze najczęstszy, lub drugi najczęstszy element.
// Dobite po conteście.

#include <bits/stdc++.h>
using namespace std;
int n, m, x, sum, ans;
vector<int> t[1 << 20], res;
priority_queue<pair<int, int> > pq;
void pp(pair<int, int> o) { cout << "|" << o.first << " " << o.second << "|\n"; }
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x, x++, t[(x % m)].push_back(i);
    for (int i = 0; i < m; i++)
        if (!t[i].empty()) pq.push({t[i].size(), i});
    while (pq.size() > 1) {
        pair<int, int> a = pq.top();
        pq.pop();
        pair<int, int> b = pq.top();
        pq.pop();
        if ((sum + a.second) % m != m - 1) {
            sum += a.second;
            sum %= m;
            if (sum == m - 1) ans++, sum = 0;
            res.push_back(t[a.second].back());
            t[a.second].pop_back();
            if (!t[a.second].empty()) pq.push({t[a.second].size(), a.second});
            pq.push(b);
        } else {
            sum += b.second;
            sum %= m;
            if (sum == m - 1) ans++, sum = 0;
            res.push_back(t[b.second].back());
            t[b.second].pop_back();
            if (!t[b.second].empty()) pq.push({t[b.second].size(), b.second});
            pq.push(a);
        }
    }
    while (!pq.empty()) {
        pair<int, int> a = pq.top();
        pq.pop();
        sum += a.second;
        sum %= m;
        if (sum == m - 1 && a.first != 1) ans++, sum = 0;
        res.push_back(t[a.second].back());
        t[a.second].pop_back();
        if (!t[a.second].empty()) pq.push({t[a.second].size(), a.second});
    }
    cout << ans << "\n";
    for (auto i : res) cout << i << " ";
}
