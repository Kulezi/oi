// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m_1*m_2 * log(m_1*m_2))
// Punkty: 20

#include <bits/stdc++.h>
using namespace std;
int m1, x, val, p1[1 << 20], p2[1 << 20], res, m2, n1, n2;
char c;
vector<int> v1, v2;
set<pair<int, int> > s1;
int main() {
    cin >> m1;
    for (int i = 1; i <= m1; i++) {
        cin >> c >> x;
        n1 += x;
        val = (c == 'T' ? 1 : 0);
        while (x--) {
            v1.push_back(val);
        }
    }
    cin >> m2;
    for (int i = 1; i <= m2; i++) {
        cin >> c >> x;
        n2 += x;
        val = (c == 'T' ? 1 : 0);
        while (x--) {
            v2.push_back(val);
        }
    }
    for (int i = 0; i < v1.size(); i++) p1[i + 1] = p1[i] + v1[i];
    for (int i = 0; i < v2.size(); i++) p2[i + 1] = p2[i] + v2[i];
    for (int i = 1; i <= n1; i++)
        for (int j = 1; j <= i; j++) s1.insert({p1[i] - p1[j - 1], i - j});
    for (int i = 1; i <= n2; i++)
        for (int j = 1; j <= i; j++)
            if (s1.count({p2[i] - p2[j - 1], i - j})) res = max(res, i - j + 1);
    cout << res;
}