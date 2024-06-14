// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(wynik * n + m)
// Złożoność pamięciowa: O(n + m)
// Punkty: 100

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
constexpr int INF = 1'000'000'000;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1), scale;
    
    for (int i = 1; i <= n; i++) cin >> a[i], scale.push_back(a[i]);
    for (int i = 1; i <= m; i++) cin >> b[i], scale.push_back(b[i]);

    sort(all(scale));
    scale.erase(unique(all(scale)), scale.end());
    int MAX_CH = scale.size();

    
    // Dla każdej z wartości tworzymy posortowane listy indeksów na których występuje w ciągu a.
    // Żeby potem znajdować następne wystąpienie literki w O(log(n)).
    vector<vector<int>> occurences_a(MAX_CH, vector<int>());

    if (n > m) {
        swap(n, m);
        swap(a, b);
    }

    // Przeskalowujemy wartości, żeby były równe max n + m.
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(all(scale), a[i]) - scale.begin();
        occurences_a[a[i]].push_back(i);
    }

    for (int i = 1; i <= m; i++) {
        b[i] = lower_bound(all(scale), b[i]) - scale.begin();
    }

    scale.clear();

    int max_ans = n / 2;
    int ans = 0;

    // dp_{wynik, i} oznacza minimalną długość prefiksu b,
    // że ma zająknięcie o długości 2*wynik na prefiksie ciągu a długości i, jak nie ma to ustawiamy na nieskończoność.
    // Da się go wyliczyć korzystając tylko z wartości z wynik-1, więc trzymamy tylko dla obecnego wyniku i następnego.
    vector<int> dp(n + 1, INF), next_dp(n + 1, INF);
    dp[0] = 0;

    vector<int> next_a(n + 1, n + 1), b_ls(n + 1, 0), b_rs(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int ch = a[i + 1];
        auto it = upper_bound(all(occurences_a[ch]), i + 1);
        if (it == occurences_a[ch].end())
            next_a[i] = n + 1;
        else
            next_a[i] = *it;
    }

    for (int wynik = 0; wynik <= max_ans; wynik++) {
        for (int i = 0; i < n; i++) {  // TODO: wlicz n do wyniku.
            int a_l = i + 1;
            int ch = a[a_l];

            // Jakbym nie wziął tej literki, to wynik mi się nie zmieni, a
            // prefiks zwiększy o 1.
            if (dp[i + 1] > dp[i]) dp[i + 1] = dp[i];

            // Jakbym wziął tę literkę, to w słowie a następną będę mógł wziąć
            // dopiero po jej nastepnym wystąpieniu (biorę ją i najbliższą na
            // prawo).
            int a_r = next_a[i];
            if (a_r > n) continue;

            int b_l = max(b_ls[i], dp[i] + 1);
            while (b_l <= m && b[b_l] != ch) b_l++;

            int b_r = max(b_l + 1, b_rs[i]);
            while (b_r <= m && b[b_r] != ch) b_r++;

            b_ls[i] = b_l;
            b_rs[i] = b_r;
            if (b_r > m) continue;

            next_dp[a_r] = min(next_dp[i], b_r);
            ans = wynik + 1;
        }

        if (ans == wynik) break;

        swap(dp, next_dp);
        next_dp = vector<int>(n + 1, INF);
    }

    cout << 2 * ans << "\n";
}