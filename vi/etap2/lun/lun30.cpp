// Rozwiązanie do zadania 'Lunatyk' z II etapu VI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(k^2)
// Złożoność pamięciowa: O(k)
// Punkty: 30 (upsolve, brak bignumów)

#include <bits/stdc++.h>
using namespace std;
using Number = long long;

int ord[3][3] = {{0, 7, 8}, {1, 6, 5}, {2, 3, 4}};
string trans = "aadddcbbd";
Number id(Number x, Number y, Number quad_len) {
    
    cerr << (int)x << " " << (int)y  << " " << (int)quad_len << endl;
    if (quad_len == 1) return ord[x][y];

    // Obetnij wspolrzedne do tego kwadratu.
    Number quad_x = x / quad_len;
    Number quad_y = y / quad_len;
    x -= quad_x * quad_len;
    y -= quad_y * quad_len;
    int quad = ord[quad_x][quad_y];

    // W zależności od współrzędnej obróć / zamień miejscami.
    switch (trans[quad]) {
        case 'a':
            swap(x, y);
            break;
        case 'b':
            swap(x, y);
        case 'c':
            x = quad_len - x - 1;
            y = quad_len - y - 1;
            break;
    }

    return id(x, y, quad_len / 3) + quad_len * quad_len * quad;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int k;
    cin >> k;

    Number src_x, src_y;
    cin >> src_x >> src_y;

    src_x--, src_y--;
    Number dst_x, dst_y;
    cin >> dst_x >> dst_y;
    dst_x--, dst_y--;

    Number pow3 = 1;
    for (int i = 1; i < k; i++) pow3 *= 3;

    Number ans = id(dst_x, dst_y, pow3) - id(src_x, src_y, pow3);
    cout << ans << "\n";
}