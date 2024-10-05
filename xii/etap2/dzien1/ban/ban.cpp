// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*k*log(k))
// Złożoność pamięciowa: O(n*k)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXC = 20005, MAXN = 205, INF = 1e8;

int dp[MAXC], oldp[MAXC], C[MAXC][MAXN], b[MAXN], res[MAXC], c[MAXC];
int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    int k;
    cin >> k;
    for (int i = 1; i <= k; i++) dp[i] = INF;

    for (int i = 1; i <= n; i++) {
        for (int beg = 0; beg < b[i]; beg++) {
            deque<int> dq;

            // Ten for loop robi k / b[i] iteracji, czyli sumarycznie bedzie O(n * k * log(k)) z sum harmonicznych.
            for (int num = 0; beg + num * b[i] <= k; num++) {
                oldp[num] = dp[beg + num * b[i]] - num;
                while (!dq.empty() && oldp[num] <= oldp[dq.back()])
                    dq.pop_back();

                dq.push_back(num);
                dp[beg + num * b[i]] = oldp[dq.front()] + num;
                C[beg + num * b[i]][i] = num - dq.front();
                if (num - dq.front() == c[i]) dq.pop_front();
            }
        }
    }

    cout << dp[k] << "\n";
    int num = n;
    while (k) {
        res[num] += C[k][num];
        k -= C[k][num] * b[num];
        num--;
    }

    for (int i = 1; i <= n; i++) cout << res[i] << " ";
}