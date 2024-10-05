// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*m*log(nm))
// Złożoność pamięciowa: O(n*m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
struct edg {
    int a, b, w, idx;
};
bool comp(edg a, edg b) { return a.w < b.w; }
int akt, m, n, r[1 << 20], res, ful, idx, cisy, zyw[1 << 23];
vector<edg> v;
string s;
int Find(int v) {
    if (r[v] == v) return v;
    return r[v] = Find(r[v]);
}
void Union(int a, int b) {
    int ra = Find(a);
    int rb = Find(b);
    r[ra] = rb;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        cin >> s;
        for (int j = 1; j < n; j++)
            idx++, v.push_back(
                       {akt + j, akt + j + 1, (s[j - 1] == 'C' ? 1 : 0), idx});
        akt += n;
    }
    akt = 0;
    for (int i = 1; i <= m - 1; i++) {
        cin >> s;
        for (int j = 1; j <= n; j++)
            idx++, v.push_back(
                       {akt + j, akt + j + n, (s[j - 1] == 'C' ? 1 : 0), idx});
        akt += n;
    }
    ful = idx;
    for (int i = 1; i <= m * n; i++) r[i] = i;
    sort(v.begin(), v.end(), comp);
    for (auto i : v) {
        if (i.w == 1) cisy++;
        if (Find(i.a) != Find(i.b)) {
            zyw[i.idx] = 1;
            ful--;
            if (i.w == 1) cisy--;
            Union(i.a, i.b);
        }
    }
    idx = 0;
    cout << ful << " " << cisy << "\n";
    for (int i = 1; i <= m; i++) {
        cin >> s;
        for (int j = 1; j < n; j++) idx++, cout << (zyw[idx] ? '.' : 'Z');
        akt += n;
        cout << "\n";
    }
    akt = 0;
    for (int i = 1; i <= m - 1; i++) {
        cin >> s;
        for (int j = 1; j <= n; j++) idx++, cout << (zyw[idx] ? 'Z' : '.');
        akt += n;
        cout << "\n";
    }
}