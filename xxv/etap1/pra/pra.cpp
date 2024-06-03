// Autor: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Punkty: 100

// Zamiatamy przedziały od lewej do prawej utrzymując kolejkę priorytetową rozmiaru k.
#include <bits/stdc++.h>
#define pu putchar_unlocked
#define f first
#define s second
using namespace std;
pair<int, int> t[1 << 20], s[1 << 20];
int a, b, n, res, l, p, k, temp;
priority_queue<int, vector<int>, greater<int> > pq;
inline void fi(int &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
inline void fo(int x) {
    if (x > 0) fo(x / 10), pu(x % 10 + '0');
}
int main() {
    fi(n);
    fi(k);
    for (int i = 1; i <= n; i++) fi(t[i].f), fi(t[i].s), s[i] = t[i];
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++) {
        pq.push(s[i].s);
        if (pq.size() > k) pq.pop();
        if (pq.size() == k && res < pq.top() - s[i].f) {
            res = pq.top() - s[i].f, l = s[i].f, p = pq.top();
        }
    }
    fo(res);
    pu('\n');
    for (int i = 1; i <= n; i++) {
        if (temp < k && t[i].s >= p && t[i].f <= l) temp++, fo(i), pu(' ');
    }
}
