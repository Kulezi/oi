// Rozwiązanie do zadania 'Skalniak' z II etapu XIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 2'000'000'000;
int n;
int x[MAXN], y[MAXN], mass[MAXN];

struct Rectangle {
    int min_x, max_x, min_y, max_y;

    bool covers(int x, int y) { return x >= min_x && x <= max_x && y >= min_y && y <= max_y; }
};

int min_masa(Rectangle rect) {
    int wynik = 0;
    for (int i = 1; i <= n; i++) {
        if (!rect.covers(x[i], y[i]) && !rect.covers(y[i], x[i])) return INF;
        if (!rect.covers(x[i], y[i])) {
            wynik += mass[i];
        }
    }

    return wynik;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;

    int max_x = 0, max_y = 0;
    int min_x = INF, min_y = INF;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i] >> mass[i];
        int mi = min(x[i], y[i]);
        int mx = max(x[i], y[i]);

        min_x = min(min_x, mi);
        max_x = max(max_x, mi);

        min_y = min(min_y, mx);
        max_y = max(max_y, mx);
    }

    long long obwod = 2LL * (max_x - min_x + max_y - min_y);

    Rectangle best{min_x, max_x, min_y, max_y};
    Rectangle yyxx{min_y, max_y, min_x, max_x};
    Rectangle xyyx{min_x, max_y, min_y, max_x};
    Rectangle yxxy{min_y, max_x, min_x, max_y};
    
    if (min_masa(best) > min_masa(yyxx)) best = yyxx;
    if (min_masa(best) > min_masa(xyyx)) best = xyyx;
    if (min_masa(best) > min_masa(yxxy)) best = yxxy;

    cout << obwod << " " << min_masa(best) << "\n";

    for (int i = 1; i <= n; i++) {
        if (!best.covers(x[i], y[i])) {
            cout << '1';
        } else {
            cout << '0';
        }
    }
    cout << "\n";
}