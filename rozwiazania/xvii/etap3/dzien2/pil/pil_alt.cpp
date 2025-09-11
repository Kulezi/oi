// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <cassert>
#include <deque>
#include <algorithm>
using namespace std;

struct kmax {
    deque<pair<int,int>> dq;
    void dodaj(int x, int pos) {
        while (!dq.empty() && dq.back().first < x) dq.pop_back();
        dq.push_back({x, pos});
    }

    void usun(int i) {
        assert(!dq.empty() && dq.front().second >= i);
        if (dq.front().second == i) dq.pop_front();
    }

    int get() {
        return dq.front().first;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, t;
    cin >> t >> n;

    int j = 1;

    kmax mi, mx;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx.dodaj(x, i);
        mi.dodaj(-x, i);
        while (mx.get() - (-mi.get()) > t) {
            mx.usun(j);
            mi.usun(j);
            j++;
        }
        
        ans = max(ans, i - j + 1);
    }

    cout << ans << "\n";
}