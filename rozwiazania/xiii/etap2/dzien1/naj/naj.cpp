// Rozwiązanie brutalne do zadania 'Najazd'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3 + n*m)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 605, INF = 2'000'000'000, MAXM = 10005;
struct Punkt {
    int x, y, waga;
} wielokat[MAXN], fabryki[MAXM];

// pizza[i][j] = Suma punktów w środku trójkąta zaczepionego w punktach (i, j-1, j).
int pizza[MAXN][MAXN];

// Suma punktów na lewo od odcinka zaczepionego w punktach wielokąta (i, j).
int f[MAXN][MAXN];

int det(Punkt a, Punkt b, Punkt p) {
    b.x -= a.x;
    p.x -= a.x;
    b.y -= a.y;
    p.y -= a.y;
    return b.x * p.y - b.y * p.x;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> wielokat[i].x >> wielokat[i].y;

    int m;
    cin >> m;

    int sum = 0;
    for (int i = 0; i < m; i++) {
        auto &f = fabryki[i];
        cin >> f.x >> f.y >> f.waga;
        sum += f.waga;
    }

    for (int j = 0; j < m; j++) {
        auto &f = fabryki[j];
        int k = 1;
        for (int i = 0; i < n; i++) {
            while (i != k && det(wielokat[i], wielokat[k], f) <= 0) k = (k + 1) % n;
            pizza[i][k] += f.waga;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j != i; j = (j + 1) % n) f[i][j] = f[i][(j - 1 + n) % n] + pizza[i][j];

    int wynik = -INF;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int c = b + 1; c < n; c++) {
                int triangle = sum - f[a][b] - f[b][c] - f[c][a];
                if (triangle > wynik) wynik = triangle;
            }
        }
    }

    cout << wynik << "\n";
}