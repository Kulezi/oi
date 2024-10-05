// Paweł Putra
// Złożoność czasowa: O(n*log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, q, a[2000005], sum;
void dft(vector<int> &p, int Q) {
    int N = p.size();
    if (N == 1) return;
    vector<int> par(N / 2), npar(N / 2);
    for (int i = 0; 2 * i < N; i++) {
        par[i] = p[i * 2];
        npar[i] = p[i * 2 + 1];
    }
    dft(par, (Q * Q) % m);
    dft(npar, (Q * Q) % m);
    int w = Q;
    for (int i = 0; 2 * i < N; i++) {
        p[i] = (par[i] + w * npar[i]) % m;
        w = (w * Q) % m;
    }
    for (int i = 0; 2 * i < N; i++) {
        p[i + N / 2] = ((par[i] + w * npar[i]) % m + m) % m;
        w = (w * Q) % m;
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> q;
    q %= m;
    vector<int> wek;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        wek.push_back(a[i] % m);
    }
    dft(wek, q);
    for (auto i : wek) sum = (sum + i) % m;
    cout << sum << "\n";
    for (auto i : wek) cout << i << " ";
}