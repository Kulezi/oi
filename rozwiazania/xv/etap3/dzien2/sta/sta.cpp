// Rozwiązanie do zadania 'Stacja' z III etapu XV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)
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

// Szybkie wczytywanie, na szkopule skraca czas działania o połowę.
void fin(int &x) {
    register char c = 0;
    x = 0;

    // Spacje, entery i EOF < '0' w ASCII a tylko to dostaniemy w inpucie poza cyframi.
    while (c < '0') c = getchar_unlocked();
    do {
        // x = x * 10 + obecna cyfra
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c >= '0');
}

int32_t main() {
    fin(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        fin(a);
        fin(b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);
    for (int i = 1; i <= n; i++) S += d[i];
    reroot(1);
    cout << wynik << "\n";
}