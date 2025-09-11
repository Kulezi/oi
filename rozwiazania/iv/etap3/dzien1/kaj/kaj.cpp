// Rozwiązanie do zadania 'Kajaki' z III etapu IV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n + w)
// Złożoność pamięciowa: O(w)
// Punkty: 100 (upsolve)

#include <algorithm>
#include <iostream>
using namespace std;
constexpr int MAXW = 200;
int cnt[MAXW + 5];

int32_t main() {
    ios_base::sync_with_stdio(0);
    int w;
    cin >> w;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int large = MAXW, ans = 0;
    for (int small = 0; small <= MAXW; small++) {
        while (cnt[small]) {
            while (small < large && (cnt[large] == 0 || small + large > w)) large--;
            ans++;
            cnt[small]--;
            if (cnt[large] && small + large <= w) {
                cnt[large]--;
            }
        }
    }

    cout << ans << "\n";
}