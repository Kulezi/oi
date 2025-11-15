// Rozwiązanie do zadania 'Telefony' z II etapu XXXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log^2(n)), bo każdą literkę słowa szukanego w mapie sprawdzę max log(n) razy.
// Złożoność pamięciowa: (n).
// Punkty: 100 (dziwi mnie, że nie mniej)



#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 500'005;
ll h[MAXN];
int vis[MAXN];
vector<int> g[MAXN], sasiedzi[MAXN];

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll R(ll a, ll b) {
    return uniform_int_distribution<ll>(a, b)(rng);
}

void dfs(int u) {
    vis[u] = 1;
    for (auto v : g[u]) {
        if (!vis[v]) {
            cout << u << " " << v << "\n";
            dfs(v);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
        
    if (n == 1) {
        cout << "1\n"
             << "1\n";
        return 0;
    }

    map<vector<int>, int> numer;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;

            if (x > i && (sasiedzi[i].empty() || sasiedzi[i].back() < i))
                    sasiedzi[i].push_back(i);
            sasiedzi[i].push_back(x);
        }
        if (sasiedzi[i].empty() || sasiedzi[i].back() < i)
            sasiedzi[i].push_back(i);

        if (!numer.count(sasiedzi[i]))
            numer[sasiedzi[i]] = numer.size() + 1; 
    }

    // Jedyny przypadek jak reprezentacja jest niejednoznaczna to jak wszyscy mają te same sąsiedztwo wliczając siebie.
    // Wtedy możemy zawsze zrobić drzewo o 2 wierzchołkach dla n >= 2.
    if (numer.size() == 1) {
        cout << "2\n" 
             << "1";
        for (int i = 2; i <= n; i++) cout << " 2";
        cout << "\n"
             << "1 2\n";

        return 0;
    }
    
    for (int i = 1; i <= n; i++) h[i] = numer[sasiedzi[i]];

    int m = numer.size();
    cout << numer.size() << "\n";
    for (int i = 1; i <= n; i++) {
        cout << h[i] << " ";

        for (auto j : sasiedzi[i]) {
            if (h[i] != h[j]) g[h[i]].push_back(h[j]);
        }
    }

    cout << "\n";
    // Żeby nie wypisać żadnej krawędzi więcej niż raz po prostu wypiszę je dfsem.
    dfs(1);

}
