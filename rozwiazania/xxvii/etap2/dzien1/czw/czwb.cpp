// Rozwiązanie brutalne do zadania 'Drzewo czwórkowe' z II etapu XXVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(4^m)
// Złożoność pamięciowa: O(4^m)
// Punkty: 24 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005, MOD = 1'000'000'007, INF = 2'000'000'000, MAXCOORD = 2050;
string s;

int t[MAXCOORD][MAXCOORD];
int maluj(int pos, int lx, int rx, int ly, int ry) {
    if (s[pos] == '0' || s[pos] == '1') {
        for (int x = lx; x <= rx; x++) {
            for (int y = ly; y <= ry; y++) {
                t[x][y] = s[pos] - '0';
            }
        }
        return 1;
    }

    int rozmiar = 1;
    int mx = (lx + rx) / 2;
    int my = (ly + ry) / 2;
    rozmiar += maluj(pos + rozmiar, lx, mx, ly, my);
    rozmiar += maluj(pos + rozmiar, mx + 1, rx, ly, my);
    rozmiar += maluj(pos + rozmiar, lx, mx, my + 1, ry);
    rozmiar += maluj(pos + rozmiar, mx + 1, rx, my + 1, ry);
    return rozmiar;
}

int vis[MAXCOORD][MAXCOORD];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

int spojne, max_rozmiar;
void bfs(int x, int y) {
    int rozmiar = 1;
    vis[x][y] = 1;
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (t[nx][ny] == 1 && !vis[nx][ny]) {
                rozmiar++;
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }

    spojne++;
    if (rozmiar > max_rozmiar) max_rozmiar = rozmiar;
}

int32_t main() {
    int n;
    cin >> n;
    cin >> s;

    maluj(0, 1, 1 << n, 1, 1 << n);

    for (int x = 1; x <= (1 << n); x++) {
        for (int y = 1; y <= (1 << n); y++) {
            if (t[x][y] && !vis[x][y]) bfs(x, y);
        }
    }

    cout << spojne << "\n";
    cout << max_rozmiar << "\n";
}
