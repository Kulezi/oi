// Autor rozwiązania: Paweł Putra
// Złożoność czasowa O(n^2*log(n)) o ile założenia z zadania nie czynią tego n*log(n).
// Punkty: 100, OI miał słabe testy :)

// Oblicza reachability nie korzystając z obserwacji z zadania, bo źle je przeczytałem.
// Wylicza zbiory wierzchołków osiągalnych z X w kolejności topologicznej.
// Żeby oszczędzić na czasie, zbiór wierzchołka jest przepinany do jakiegoś przodka 
// (chyba tego z największym stopniem, już nie pamiętam co wtedy myślałem)

// cancer2k18 bedzie 0
#include <bits/stdc++.h>
using namespace std;
const int MX = 50005;
int n, m, a, b, kolor, pre[MX], low[MX], czas, visit[MX], sccsize[MX], wyn[MX], scc[MX], N, st[MX],
    sum[MX], setidx[MX], wch[MX];
vector<int> g[MX], sccg[MX], sccv[MX], rew[MX], stos;
set<int> res[MX];
queue<int> q;
void getlow(int v) {
    low[v] = pre[v] = ++czas;
    stos.push_back(v);
    for (auto u : g[v]) {
        if (!scc[u]) {
            if (!pre[u]) {
                getlow(u);
                low[v] = min(low[v], low[u]);
            } else if (pre[u])
                low[v] = min(low[v], pre[u]);
        }
    }
    if (low[v] == pre[v]) {
        N++;
        while (1) {
            int u = stos.back();
            scc[u] = N;
            stos.pop_back();
            if (u == v) break;
        }
    }
}
bool comp(int a, int b) { return wch[a] < wch[b]; }
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        kolor++;
        setidx[i] = i;
        if (!pre[i]) getlow(i);
        //   cerr << scc[i] << " ";
    }  // cerr<<endl;
    for (int i = 1; i <= n; i++) {
        sccsize[scc[i]]++;
        sccv[scc[i]].push_back(i);
        while (!g[i].empty()) {
            a = scc[i];
            b = scc[g[i].back()];
            if (a != b) sccg[a].push_back(b), rew[b].push_back(a);
            g[i].pop_back();
        }
    }
    for (int i = 1; i <= N; i++) {
        st[i] = sccg[i].size();
        wch[i] = rew[i].size();
        // cout << sccsize[i] << " ";
        if (st[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int v = q.front();
        // cout << v << " ";
        for (auto u : rew[v]) {
            st[u]--;
            if (st[u] == 0) q.push(u);
        }
        sort(sccg[v].begin(), sccg[v].end(), comp);
        for (auto u : sccg[v]) {
            if (wch[u] == 1 && setidx[v] == v) {  // cout << " L ";
                setidx[v] = setidx[u];
                res[setidx[v]].insert(u);
                sum[v] = sum[u];
                sum[v] += sccsize[u];
                //  cout << sum[v];
            } else if (!res[setidx[v]].count(u)) {
                res[setidx[v]].insert(u);
                sum[v] += sccsize[u];
                for (auto i : res[setidx[u]]) {
                    if (!res[setidx[v]].count(i)) res[setidx[v]].insert(i), sum[v] += sccsize[i];
                }
                // cout << " R " << u << " "<< sum[v];
            }
            wch[u]--;
        }
        q.pop();
        // cout<<endl;
    }
    for (int i = 1; i <= N; i++) {
        for (auto j : sccv[i]) wyn[j] = sum[i] + sccsize[i] - 1;
    }
    for (int i = 1; i <= n; i++) cout << wyn[i] << "\n";
}