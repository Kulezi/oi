// Autor rozwiązania: Paweł Putra
// Złożoność czasowa O((n+m)*log(n))
// Punkty: 100

// Leniwe drzewo przedziałowe funkcji liniowych.
#include <bits/stdc++.h>
#define int long long
using namespace std;
int sum[1 << 21], lazya[1 << 21], lazyb[1 << 21], ql, qp, n, a, b, m;
int getsum(int pos, int l, int p) {
    int aa = lazya[pos];
    int bb = lazyb[pos];
    int wartwp = aa * p + bb;
    int wartwl = aa * l + bb;
    int ile = p - l + 1;
    int zajebiscie = ile / 2 * (wartwp + wartwl);
    if (ile % 2 == 1) zajebiscie += (wartwp + wartwl) / 2;
    return zajebiscie;
}
int getsum2(int aa, int bb, int l, int p) {
    int wartwp = aa * p + bb;
    int wartwl = aa * l + bb;
    int ile = p - l + 1;
    int zajebiscie = ile / 2 * (wartwp + wartwl);
    if (ile % 2 == 1) zajebiscie += (wartwp + wartwl) / 2;
    return zajebiscie;
}
void update(int pos, int l, int p, int fa, int fb) {
    if (l > qp || p < ql) return;

    if (l >= ql && p <= qp) {  //  cout << l << " " << p << endl;
        //  cout << "eluwa"<<endl;
        lazya[pos] += fa;
        lazyb[pos] += fb;
        return;
    }
    int mid = (l + p) / 2;
    update(pos * 2, l, mid, fa, fb);
    update(pos * 2 + 1, mid + 1, p, fa, fb);  //-fa*(mid+1-l)+fb);
    //    cout << l << " " << p << endl;
    // cout << " " << sum[pos*2] << " " << sum[pos*2+1] << " " << getsum(pos*2,l,mid) << " " <<
    // getsum(pos*2+1,mid+1,p)<<endl;
    sum[pos] =
        sum[pos * 2] + sum[pos * 2 + 1] + getsum(pos * 2, l, mid) + getsum(pos * 2 + 1, mid + 1, p);
}
int query(int pos, int l, int p, int fa, int fb) {
    if (l > qp || p < ql) return 0;
    if (l >= ql && p <= qp) {
        fa += lazya[pos];
        fb += lazyb[pos];
        return sum[pos] + getsum2(fa, fb, l, p);
    }
    int mid = (l + p) / 2;
    return query(pos * 2, l, mid, fa + lazya[pos], fb + lazyb[pos]) +
           query(pos * 2 + 1, mid + 1, p, fa + lazya[pos],
                 fb + lazyb[pos]);  //+(-(fa+lazya[pos])*(mid+1-l)));
}
int vals[500005], rozs[500005], roz, val, x;
char c;
main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> c;
        if (c == 'P') {
            cin >> x >> val >> roz;
            vals[x] = val;
            rozs[x] = roz;
            int zasieg = (val - 1) / roz;
            ql = x;
            qp = min(x + zasieg, n);
            a = -roz;
            b = val + roz * x;
            //  cout << ql << " " << qp << " " << a << " " << b << endl;
            update(1, 1, n, a, b);

            if (zasieg > 0 && x - 1 > 0) {
                ql = x - zasieg;
                qp = x - 1;
                a = roz;
                b = val + -roz * x;
                update(1, 1, n, a, b);
            }
        } else if (c == 'U') {
            cin >> x;
            val = vals[x];
            roz = rozs[x];
            int zasieg = (val - 1) / roz;
            ql = x;
            qp = min(x + zasieg, n);
            a = -roz;
            b = val + roz * x;
            //  cout << ql << " " << qp << " " << a << " " << b << endl;
            update(1, 1, n, -a, -b);

            if (zasieg > 0 && x - 1 > 0) {
                ql = x - zasieg;
                qp = x - 1;
                a = roz;
                b = val + -roz * x;
                update(1, 1, n, -a, -b);
            }
        } else {
            cin >> ql >> qp;
            cout << query(1, 1, n, 0, 0) / (qp - ql + 1) << endl;
        }
    }
    // for(int i=1;i<=13;i++)cout<<sum[i]<<" ";
}

/*
 int jeden=lazya[pos]*l+lazyb[pos];
        int dwa=lazya[pos]*p+lazyb[pos];
        int a = abs(jeden-dwa);
        int b = p-l+1;
        tree[pos]+=((a*b)>>1);
*/