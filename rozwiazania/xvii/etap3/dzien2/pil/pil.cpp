// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int n, T, res, l = 1, x;
deque<pii> mi, mx;

int main() {
    scanf("%d%d", &T, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        while (!mx.empty() && mx.back().first <= x) mx.pop_back();
        while (!mi.empty() && mi.back().first >= x) mi.pop_back();
        mx.push_back({x, i});
        mi.push_back({x, i});

        while (mx.front().first - mi.front().first > T) {
            if (mi.front().second == l) mi.pop_front();
            if (mx.front().second == l) mx.pop_front();
            l++;
        }

        res = max(res, i - l + 1);
    }

    printf("%d\n", res);
}