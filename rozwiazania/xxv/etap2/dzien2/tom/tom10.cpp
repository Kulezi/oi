// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*log(n))
// Punkty: 10

// Brut przeglądający wszystkie permutacje.
#include <bits/stdc++.h>
using namespace std;
int n, s, t[1 << 20], akt, ans = INT_MAX, res;
vector<pair<int, int> > v, vans;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        t[i]++;
        v.push_back({t[i], i});
    }
    sort(v.begin(), v.end());
    do {
        res = 0;
        akt = 0;
        for (int i = 0; i < n - 1; i++) {
            akt += v[i].first;
            akt %= s;
            if (akt == s - 1) akt = 0, res++;
        }
        if (ans > res) {
            ans = res;
            vans = v;
        }
    } while (next_permutation(v.begin(), v.end()));
    cout << ans << "\n";
    for (auto i : vans) cout << i.second << " ";
}