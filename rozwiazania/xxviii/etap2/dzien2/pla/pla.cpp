// Rozwiązanie do zadania 'Plażowicze' z II Etapu XXVIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log^2(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005, MAXZ = 1'000'05;
constexpr ll OFFSET = 1 << 30;
int n, X, z;
int x[MAXN];
int cnt[MAXN];
// (indeks startu, ktora dziura, ile dziur)
tuple<int, int, int> odp[MAXZ];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> X >> z;

    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    vector<pair<int, int>> zapytania;
    for (int i = 1; i <= z; i++) {
        int k;
        cin >> k;
        zapytania.push_back({k, i});
    }

    sort(zapytania.begin(), zapytania.end());

    // (wielkość dziury, -gdzie ta dziura, ile takich dziur)
    priority_queue<pair<ll, int>> pq;
    for (int i = 1; i < n; i++) {
        cnt[i] = 1;

        // Domnażamy przez dużą potęgę dwójki, żeby nie bawić sie w ułamki.
        pq.push({OFFSET * (x[i + 1] - x[i]), -i});
    }

    int posadzeni = 0;
    for (auto [k, zap_idx] : zapytania) {
        auto [L, start] = pq.top();
        while (posadzeni + cnt[-start] < k) {
            posadzeni += cnt[-start];
            pq.pop();
            pq.push({L >> 1, start});
            cnt[-start] *= 2;
            tie(L, start) = pq.top();
        }

        tie(L, start) = pq.top();
        odp[zap_idx] = {-start, k - posadzeni, cnt[-start]};
    }

    for (int i = 1; i <= z; i++) {
        auto [idx, ktora, ile] = odp[i];
        int L = x[idx], R = x[idx + 1];
        ll licznik = 2LL * ile * L + 1LL * (R - L) * (1 + 2 * (ktora - 1));
        ll mianownik = 2LL * ile;
        ll g = __gcd(licznik, mianownik);
        cout << licznik / g << "/" << mianownik / g << "\n";
    }
}