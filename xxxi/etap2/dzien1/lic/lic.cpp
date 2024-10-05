// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int INF = 1e9;
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;


    vector<int> c(n);
    for (auto &i : c) cin >> i;

    vector<pii> meters;
    for (int i = 0; i < n; i++) {
        int meter;
        cin >> meter;
        meters.emplace_back(meter, c[i]);
    }
    
    // Jak przychodzą nowe wskazania liczników,
    // To przypisuję je w kolejności od najniższego do najwyższego,
    // do nieprzypisanego licznika o najwyższej cenie za litr
    // a w przypadku remisu do tego, o najniższym dotychczasowym wskazaniu.

    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        vector<int> liters(n);
        for (auto &j : liters) cin >> j;

        sort(all(liters));
        sort(all(meters));

        // Na szczycie kolejki priorytetowej zawsze będzie najdroższy licznik
        // na którym wskazanie nie przekroczyło l litrów.
        priority_queue<pii> pq;
        int j = -1;

        vector<pii> new_meters;
        for (auto l : liters) {
            while (j + 1 < n && meters[j+1].first <= l) {
                j++;
                pq.push({meters[j].second, meters[j].first});
            }

            if (pq.empty()) {
                cout << "NIE\n";
                return 0;
            }

            auto [price, old_liters] = pq.top();
            pq.pop();

            ans += 1LL * price * (l - old_liters); 
            new_meters.push_back({l, price});
        }

        meters = new_meters;        
    }

    cout << ans << "\n";
}