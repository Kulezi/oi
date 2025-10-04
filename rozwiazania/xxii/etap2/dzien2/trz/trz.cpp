// Rozwiązanie zadania 'Trzy wieże' z II etapu XXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#define dbg(x) #x << " = " << x << " "
using namespace std;
int map(char c) {
    if (c == 'C') return 0;
    if (c == 'B') return 1;
    if (c == 'S') return 2;
    assert(false);
    return -1;
}
constexpr int MAXN = 1'000'005, KOLORY = 3;
int pref[MAXN][KOLORY];
int suma(int l, int r, int tab) {
    return pref[r][tab] - pref[l-1][tab];
}

bool rozne(int x, int y) {
    return x != y || x == 0 || y == 0;
}

bool dobry(int l, int r) {
    int a = suma(l, r, 0);
    int b = suma(l, r, 1);
    int c = suma(l, r, 2);
    return rozne(a, b) && rozne(a, c) && rozne(b, c);  
}

int res;
void maksuj(int i, int j) {
    if (j - i + 1 > res && dobry(i, j)) {
        res = j - i + 1;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    string s;
    
    cin >> n >> s;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < KOLORY; j++) {
            pref[i][j] = pref[i - 1][j];
        }

        pref[i][map(s[i-1])]++;
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = i; j <= n; j++) {
            maksuj(i, j);
            maksuj(n-j+1, n-i+1);
        }
    }

    cout << res << "\n";
}
