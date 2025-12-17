// Rozwiązanie zadania 'Temperatura' z II Etapu XVIII OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)

#include <iostream>
#include <deque>
using namespace std;
constexpr int MAXN = 1'000'005;
int t_min[MAXN], t_max[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> t_min[i] >> t_max[i];
    }


    int j = 1, wynik = 1;
    deque<int> dq;

    for (int i = 1; i <= n; i++) {
        while (j <= n && (dq.empty() || t_max[j] >= t_min[dq.front()])) { 
            while (!dq.empty() && t_min[dq.back()] < t_min[j])
                dq.pop_back();
            dq.push_back(j);
            j++;
        }

        wynik = max(wynik, j - i);

        if (dq.front() == i) dq.pop_front(); 
    }

    cout << wynik << "\n";
}
