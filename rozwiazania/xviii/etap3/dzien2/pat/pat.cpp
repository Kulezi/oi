// Rozwiązanie do zadania 'Patyczki' z III etapu XVIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int k;
    cin >> k;

    vector<pair<int, int>> patyki;
    for (int i = 1; i <= k; i++) {
        int n_i;
        cin >> n_i;
        while (n_i--) {
            int x;
            cin >> x;

            patyki.push_back({x, i});
        }
    }

    sort(patyki.begin(), patyki.end());

    pii a, b, c;
    a = b = c = {0, 0};
    for (auto [dlugosc, kolor] : patyki) {
        if (a.second == kolor) {
            swap(a, b);
            swap(b, c);
            c.first = dlugosc;
        } else if (b.second == kolor) {
            swap(b, c);
            c.first = dlugosc;
        } else if (c.second == kolor)
            c.first = dlugosc;
        else {
            swap(a, b);
            swap(b, c);
            c = {dlugosc, kolor};
        }

        if (a.first != 0 && b.first != 0 && c.first != 0 && a.first + b.first > c.first) {
            cout << a.second << " " << a.first << " ";
            cout << b.second << " " << b.first << " ";
            cout << c.second << " " << c.first << "\n";
            return 0;
        }
    }

    cout << "NIE\n";
}