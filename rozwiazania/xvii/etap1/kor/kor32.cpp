// Rozwiązanie brutalne do zadania 'Korale'.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2*log^2(n))
// Złożoność pamięciowa: O(n)
// Punkty: 32 (upsolve)

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    
    vector<int> v(n);
    for (auto &i : v) {
        cin >> i;
    }

    int max_roznych = 0;
    vector<int> jakie_k;
    for (int k = 1; k <= n; k++) {
        set<vector<int>> rozne;
        for (int l = 0; l + k - 1 < n; l += k) {
            vector<int> kawalek = vector<int>(v.begin()+l, v.begin()+l+k);
            vector<int> kawalek_rev = kawalek;
            reverse(kawalek_rev.begin(), kawalek_rev.end());

            rozne.insert(min(kawalek, kawalek_rev));
        }

        int ile_roznych = rozne.size();
        if (ile_roznych > max_roznych) {
            max_roznych = ile_roznych;
            jakie_k = {k};
        } else if (ile_roznych == max_roznych) {
            jakie_k.push_back(k);
        }
    }

    cout << max_roznych << " " << jakie_k.size() << "\n";
    for (auto i : jakie_k) cout << i << " ";
    cout << "\n";
}