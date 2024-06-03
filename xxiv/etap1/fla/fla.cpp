// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
int last,n,X,x,lo,hi,l,p;
int main()
{
    cin >> n >> X;
    for(int i=0;i<=n;i++)
    {   if(i!=n)cin >> x >> lo >> hi;
        else x = X,lo = -1000000000,hi=1000000000;
        p+=x-last;
        l-=x-last;
        p=min(p,hi-1);
        l=max(lo+1,l);
        if(abs(p%2) != x%2)p--;
        if(abs(l%2) != x%2)l++;
        if(l>p)
        {   cout << "NIE";
            return 0;
        }
        last = x;
    }
    cout << (l+x)/2;
}