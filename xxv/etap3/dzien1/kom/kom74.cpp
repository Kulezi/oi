// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(b*ln(n) + t)
// Punkty: 74

#include <bits/stdc++.h>
using namespace std;
int pref[10000005], pot = 1, q, ql[1005], qp[1005], d[10000005], cyf, maxp, maxr;
vector<int> v;
int getcyf(int x) {
    int res = 0;
    while (x > 0) x /= 10, res++;
    return res;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> ql[i] >> qp[i];
        maxp = max(maxp, qp[i]);
        maxr = max(qp[i] - ql[i], maxr);
    }
    if ((q <= 5 && maxr <= 5000000) || maxp > 10000000)

    {
        for (int rep = 1; rep <= q; rep++) {
            int wyn = 0;
            pot = 1;
            cyf = 0;
            for (int i = 1; i * i <= qp[rep]; i++) {
                if (i * i >= ql[rep]) d[(i * i) - ql[rep]]++;
                for (int j = max(i * i + i, ((ql[rep] - 1) / i + 1) * i); j <= qp[rep]; j += i)
                    d[j - ql[rep]] += 2;
            }
            while (ql[rep] >= pot) pot *= 10, cyf++;
            if (ql[rep] == pot) cyf--;
            for (int i = ql[rep]; i <= qp[rep]; i++) {
                if (i == pot) cyf++, pot *= 10;
                // cout << d[i-ql[rep]]<<" "<<cyf << " " << pot << endl;
                if (cyf == d[i - ql[rep]]) wyn++;
                d[i - ql[rep]] = 0;
            }
            cout << wyn << "\n";
        }
        return 0;
    }
    int elo = sqrt(maxp);
    for (int i = 1; i <= maxp; i++) {
        if (i <= elo) {
            d[i * i]++;
            for (int j = i * i + i; j <= maxp; j += i) {
                d[j] += 2;
            }
        } else
            break;
    }
    for (int i = 1; i <= maxp; i++) {  // cout << d[i] << " ";
        if (i == pot) cyf++, pot *= 10;
        if (cyf == d[i]) pref[i]++;
        pref[i] += pref[i - 1];
        // cout << cyf << " " << d[i] << " " << pref[i] << endl;
    }
    for (int i = 1; i <= q; i++) {
        cout << pref[qp[i]] - pref[ql[i] - 1] << "\n";
    }
}