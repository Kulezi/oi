// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Punkty: 100

// Konstrukcja oparta na grupowaniu wierzchołków z tymi samymi różnicami d(a, i) - d(b, i).
#include <bits/stdc++.h>
#define spacyjka putchar_unlocked(' ')
#define endlajn putchar_unlocked('\n')
#define f first
#define s second
using namespace std;
int n, t1[1 << 19], t2[1 << 19], dist[1 << 19][2], vis[1 << 19], minroz, maxroz, akt, roz, P, TAB;
pair<int, pair<int, int> > pq[1 << 19], res[1 << 19];
vector<pair<int, int> > g[1 << 19];
inline void fin(int &liczba) {
    register char c = 0;
    liczba = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        liczba = (liczba << 1) + (liczba << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
inline void fo(int liczba) {
    if (liczba > 0) {
        fo(liczba / 10);
        putchar_unlocked(liczba % 10 + 48);
    }
}
void connect(int a, int b) {
    int D = 1;
    if (a > b) swap(a, b);
    if (a == 1 && b == n)
        D = abs(t1[2] - t2[2]);
    else if (a == 1)
        D = t1[b];
    else if (b == n)
        D = t2[a];
    else
        D = abs(t1[a] - t1[b]);
    D = max(1, D);
    res[++P] = {a, {b, D}};
    g[a].push_back({b, D});
    g[b].push_back({a, D});
}
void dfs(int v) {
    vis[v] = 1;
    for (auto u : g[v])
        if (!vis[u.f]) dist[u.f][TAB] = dist[v][TAB] + u.s, dfs(u.f);
}
bool check() {
    for (int i = 1; i <= n; i++) vis[i] = 0;
    TAB = 0;
    dfs(1);
    for (int i = 1; i <= n; i++) vis[i] = 0;
    TAB = 1;
    dfs(n);
    // for(int i=1;i<=P;i++)cout<<"WA"<<res[i].f<<" "<<res[i].s.f<<" "<<res[i].s.s<<endl;
    // cout<<endl;
    for (int i = 2; i < n; i++)
        if (dist[i][0] != t1[i] || dist[i][1] != t2[i]) return 0;
    puts("TAK");
    for (int i = 1; i <= P; i++)
        fo(res[i].f), spacyjka, fo(res[i].s.f), spacyjka, fo(res[i].s.s), endlajn;
    return 1;
}
int main() {
    fin(n);
    for (int i = 2; i < n; i++) fin(t1[i]);
    for (int i = 2; i < n; i++) {
        fin(t2[i]);
        pq[i] = {t1[i] - t2[i], {t1[i], i}};
        minroz = min(t1[i] - t2[i], minroz);
        maxroz = max(t1[i] - t2[i], maxroz);
    }
    sort(pq + 2, pq + n);
    if (n == 2) {
        cout << "TAK" << endl << "1 2 1" << endl;
        return 0;
    }
    /// ########-LEWA SRODEK I PRAWA-#########///
    akt = 1;
    roz = minroz;
    for (int i = 2; i < n; i++) {
        int u = pq[i].s.s, w = pq[i].f;
        if (w == roz)
            connect(akt, u);
        else {
            if (w == maxroz)
                connect(akt, n), connect(n, u), akt = n;
            else
                connect(akt, u), akt = u;
            roz = w;
        }
    }
    if (check()) return 0;
    P = 0;
    /// ########-LEWA STRONA I SRODEK-########///
    akt = 1;
    roz = minroz;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 2; i < n; i++) {
        int u = pq[i].s.s, w = pq[i].f;
        if (w == roz)
            connect(akt, u);
        else
            connect(akt, u), akt = u;
        roz = w;
    }
    connect(akt, n);
    if (check()) return 0;
    P = 0;
    /// #######-SRODEK I PRAWA STRONA-#######///
    akt = 1;
    roz = 1e9;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 2; i < n; i++) {
        int u = pq[i].s.s, w = pq[i].f;
        if (w == roz)
            connect(akt, u);
        else {
            if (w == maxroz)
                connect(akt, n), connect(n, u), akt = n;
            else
                connect(akt, u), akt = u;
            roz = w;
        }
    }
    if (check()) return 0;
    P = 0;
    /// ######------SAM  SRODEK------######///
    akt = 1;
    roz = 1e9;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 2; i < n; i++) {
        int u = pq[i].s.s, w = pq[i].f;
        if (w == roz)
            connect(akt, u);
        else
            connect(akt, u), akt = u;
        roz = w;
    }
    connect(akt, n);
    if (check()) return 0;
    P = 0;
    /// ######------BRAK SRODKA------#######///
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 2; i < n; i++) {
        int u = pq[i].s.s, w = pq[i].f;
        if (w < 0)
            connect(1, u);
        else
            connect(u, n);
    }
    connect(1, n);
    if (check()) return 0;
    puts("NIE");
}
