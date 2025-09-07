// Rozwiązanie brutalne do zadania 'Turniej trójinformatyczny' z III etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^3)
// Złożoność pamięciowa: O(n^2)
// Punkty: 37

#include <bits/stdc++.h>
#define pu putchar_unlocked
using namespace std;
int n,a[1<<20],b[1<<20],c[1<<20],kolor,vis[1005][1005],l,p,q;
vector<int> g[1<<20];
int wygryw(int x,int y)
{
    int res=0;
    if(a[x]<a[y])res++;
    if(b[x]<b[y])res++;
    if(c[x]<c[y])res++;
    return res>1;
}
void dfs(int v)
{
    vis[v][kolor]=1;
    for(auto u : g[v])
    {
        if(!vis[u][kolor])
            dfs(u);
    }
}
inline void fin(int &x)
{
    register char c=0;
    x=0;
    while(c<33)c=getchar_unlocked();
    do{
        x = (x<<1)+(x<<3) + c - '0';
        c=getchar_unlocked();
    }while(c>33);
}
int main()
{
    fin(n);
    for(int i=1;i<=n;i++) fin(a[i]);
    for(int i=1;i<=n;i++) fin(b[i]);
    for(int i=1;i<=n;i++) fin(c[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {   if(i==j)continue;
            if(wygryw(i,j))g[i].push_back(j);
        }
    }
    for(kolor=1;kolor<=n;kolor++)
    {
        dfs(kolor);
    }
    fin(q);
    while(q--)
    {
        fin(l);fin(p);
        if(vis[p][l])pu('T'),pu('A'),pu('K'),pu('\n');
        else pu('N'),pu('I'),pu('E'),pu('\n');
    }
    
}
