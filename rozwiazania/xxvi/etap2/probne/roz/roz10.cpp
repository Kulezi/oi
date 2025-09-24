// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n*log(n)).
// Punkty: 10

// ej nie testowalem bedzie 0 :((
// ale jutro przetestuje obiecuje nie bedzie WA :))
// submita pewnie tez...
// mam nadzieje ze obiad bedzie smaczny
// kto by tam testowal 5 minut przed koncem
// to chyba nie ja
// pamiec: O(n + n / 8) yay
// zlozonosc O(nlogn) yay
// dziala O(niewiem) yay
#define ll long long
const int B = (1 << 16), D = 16;
ll t[1000005], tree[1 << 17];
using namespace std;
int M, N;
int getidx(int x)
{   return x / D + 1;
}
void insert(int pos, int x)
{   t[pos] += x;
    pos = getidx(pos);
    pos += B;
    while(pos > 0)
    {   tree[pos] += x;
        pos >>= 1;
    }
}
ll tquery(int a, int b)
{   ll res = 0;   
    a += B;
    while(a > 1)
    {   if(a % 2 == 1)
            res += tree[a - 1];
        a >>= 1;
    }
    b += B;
    while(b > 1)
    {   if(b % 2 == 0)
            res += tree[b + 1];
        b >>= 1;
    }
    return tree[1] - res;
}
ll query(int l, int p)
{   int lew = getidx(l);
    int praw = getidx(p);
    ll res = 0;
    if(praw - lew > 1)
        res += tquery(lew + 1, praw - 1);
    for(int i = l; i <= p && getidx(i) == lew; i++)
        res += t[i];
    if(praw != lew)
        for(int i = p; getidx(i) == praw; i--)
            res += t[i];
    return res;
}
int idx(int x)
{   return ((x - 1) % M) + 1;
}
void inicjuj(int m)
{   M = m;
    N = 0;
}
void dodaj(int k)
{   N++;
    if(N > M)
        insert(idx(N), -t[idx(N)]);
    insert(idx(N), k);
}
void koryguj(int i, int k)
{   //cerr << "KORYG " << i << " " << k  << "\n";
    insert(idx(N - i + 1), k);
    //wypiszdq();
}
ll suma(int i)
{   int p = idx(N);
    int l = idx(N - i + 1);
    if(l <= p)
        return query(l, p);
    else return query(1, p) + query(l, M);
}