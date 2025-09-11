// Rozwiązanie do zadania 'Walki robotów' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 200005;
int cnt[2 * MAXN];

int32_t main() {
    int n;
    cin >> n;

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int s, z;
        cin >> s >> z;

        cnt[s + z]++;
        mx = max(mx, s + z);
    }

    // Nie da się tylko jak występują wszystkie roboty z maksymalną sumą sił i zwinności i jest ich
    // nieparzyście wiele. W przeciwnym wypadku można jednego z nich sparować z jakimś z inną sumą a
    // resztę wyeliminować jednostronnymi pojedynkami.
    int ile_na_przekatnej = n - abs(n + 1 - mx);
    if (cnt[mx] != ile_na_przekatnej || ile_na_przekatnej % 2 == 0)
        cout << "TAK\n";
    else
        cout << "NIE\n";
}