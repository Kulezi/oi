// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*m).
// Punkty: 100

#include <bits/stdc++.h>
#define MX 2000005
using namespace std;
inline void fin(int &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
int n, m, t[MX + MX], L[32], P[32], l, p, pot[32];
long long res;
struct xd {
    int fr = 0, ba = 0, t[MX + MX];
    inline void push_back(int x) { t[ba++] = x; }
    inline void pop_front() {
        fr++;
        if (ba < fr) fr = ba = 0;
    }
    inline int front() { return t[fr]; }
    inline int empty() { return fr == ba; }
    inline int back() { return t[ba - 1]; }
} dq[30];
int main() {
    ios_base::sync_with_stdio(0);
    fin(n);
    fin(m);
    for (int i = 0; i < n; i++) pot[i] = (1 << i);
    for (int i = 1; i <= m; i++) fin(t[i]), t[i + m] = t[i];
    for (int i = 1; i < m; i++)
        for (int B = 0; B < n; B++)
            if ((t[i] & pot[B]) != (t[i + 1] & pot[B])) dq[B].push_back(i);
    for (int i = 1; i <= m; i++) {
        l = i, p = i + m - 1;
        for (int B = 0; B < n; B++) {
            while (!dq[B].empty() && dq[B].front() < i) dq[B].pop_front();
            if (!dq[B].empty()) l = max(l, dq[B].front() + 1), p = min(p, dq[B].back());
            if ((t[i + m - 1] & pot[B]) != (t[i + m] & pot[B])) dq[B].push_back(i + m - 1);
        }
        res += max(0, p - l);
    }
    cout << res / 2LL;
}
// overflow??