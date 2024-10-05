// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^2).
// Punkty: 37 (resubmit na 18 :()

#include <bits/stdc++.h>
const int MX = 1200005;
using namespace std;
set<pair<int,int> > s;
vector<pair<int,int> > g[MX];
int r[MX], spojne, n, skier[MX], a, b, vis[MX], onstack[MX], m, A[MX], B[MX], pre[MX], rev[MX], czas;
set<int> stos;
map<pair<int,int>, char> mapa;
int Find(int x)
{   if(r[x] == x)return x;
    return r[x] = Find(r[x]);
}
void Union(int a, int b)
{   int ra = Find(a), rb = Find(b);
    if(ra != rb)
        spojne--;
    r[ra] = rb;
}
void dfs(int v, int ojciec)
{   pre[v] = ++czas;
    rev[pre[v]] = v;
    onstack[v] = 1;
    vis[v] = 1;
    stos.insert(pre[v]);
  //  cout << v << "+";
   // for(auto i : stos)cout << i<< " ";
   // cout << endl;
    for(auto u : g[v])
    {   if(!vis[u.first])
        {   skier[abs(u.second)] = u.second;
            dfs(u.first, v);
        }
        else if(onstack[u.first] && u.first != ojciec)
        {   Union(v, u.first);
            skier[abs(u.second)] = u.second;
            auto it = stos.find(pre[u.first]);
            vector<int> usun;
            if(it == stos.end())continue;
            it++;
            while(it != stos.end())
            {   usun.push_back(*it);
                Union(rev[(*it)], v);
                it++;
            }
            for(auto i : usun)
                stos.erase(i);
            usun.clear();
        }
    }
    onstack[v] = 0;
    stos.erase(pre[v]);
}
int main()
{   cin >> n >> m;
    spojne = n;
    for(int i = 1; i <= n; i++)
        r[i] = i;
    for(int i = 1; i <= m; i++)
    {   cin >> a >> b;
        A[i] = a; B[i] = b;
        if(s.count({a, b}))
            Union(a, b);
        s.insert({a, b});
        s.insert({b, a});
        g[a].push_back({b, i});
        g[b].push_back({a, -i});
    }
    for(int i = 1; i <= n; i++)
    {   if(!vis[i])
            dfs(i, i);
    }
    s.clear();
    cout << spojne << "\n";
    for(int i = 1; i <= m; i++)
    {   a = A[i];
        b = B[i];
        if(a < b)swap(a, b);
        if(mapa.count({a, b}))
        {
            if(mapa[{a, b}] == '<')
                cout << '>';
            else cout << '<';
        }
        else if(skier[i] >= 0)
            cout << '>';
        else cout << '<';
            
    }
}