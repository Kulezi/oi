// Rozwiązanie do zadania 'Stacja' z III etapu XV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 97 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005;
vector<int> g[MAXN];
int sub[MAXN], d[MAXN];
void dfs(int v) {
    sub[v] = 1;
    for (auto u : g[v]) {
        if (!sub[u]) {
            d[u] = d[v] + 1;
            dfs(u);
            sub[v] += sub[u];
        }
    }
}

int n;
// Suma odległości wszystkich wierzchołków od aktualnego korzenia.
long long S = 0;
long long max_S = 0;
int wynik = 1;
void reroot(int v) {
    // Średnia = #par - S / #par => Szukamy maksymalnego S.
    if (S > max_S) {
        max_S = S;
        wynik = v;
    }

    for (auto u : g[v]) {
        if (d[u] > d[v]) {
            // Zbliżam się o jeden do każdego niżej i oddalam od każdego wyżej.
            S += (n - sub[u]) - sub[u];
            reroot(u);
            S -= (n - sub[u]) - sub[u];
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);
    for (int i = 1; i <= n; i++) S += d[i];
    reroot(1);
    cout << wynik << "\n";
}