// Paweł Putra
// Złożoność czasowa: O((m-k)*(n-k)*k)
// Punkty: 69

// Przesuwamy kwadrat "zygzakiem" po siatce, utrzymując liczbę różnych wartości w nim.
#include <cstdio>
using namespace std;
int n, m, k, t[3001][3001], C[100005], res, maxres, aktx = 2, akty = 1, temp;
long long sumres;
inline void fi(int &x) {
    register char c = 0;
    x = 0;
    while (c < 33) c = getchar_unlocked();
    do {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    } while (c > 33);
}
int main() {
    fi(m);
    fi(n);
    fi(k);
    //	m=n=3000;
    //	k=1000;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) fi(t[i][j]);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++) {
            if (!C[t[i][j]]) res++;
            C[t[i][j]]++;
        }
    sumres += res;
    if (res > maxres) maxres = res;
    if (m == k && n == k) {
    }
    if (m == k) {
        for (int i = k + 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                C[t[j][i - k]]--;
                if (!C[t[j][i - k]]) res--;
                if (!C[t[j][i]]) res++;
                C[t[j][i]]++;
            }
            sumres += res;
            if (res > maxres) maxres = res;
        }
    } else if (n == k) {
        for (int i = k + 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                C[t[i - k][j]]--;
                if (!C[t[i - k][j]]) res--;
                if (!C[t[i][j]]) res++;
                C[t[i][j]]++;
            }
            sumres += res;
            if (res > maxres) maxres = res;
        }
    } else {
        while (true) {
            if (aktx == 1) {
                temp = akty + k;
                for (int i = akty; i < temp; i++) {
                    C[t[k + 1][i]]--;
                    if (!C[t[k + 1][i]]) res--;
                    if (!C[t[1][i]]) res++;
                    C[t[1][i]]++;
                }
                sumres += res;
                if (res > maxres) maxres = res;
                akty++;
                if (akty + k - 1 > n) break;
                temp = aktx + k;
                akty--;
                for (int i = aktx; i < temp; i++) {
                    C[t[i][akty]]--;
                    if (!C[t[i][akty]]) res--;
                    if (!C[t[i][akty + k]]) res++;
                    C[t[i][akty + k]]++;
                }
                sumres += res;
                if (res > maxres) maxres = res;
                aktx++;
                akty++;
            } else if (aktx + k - 1 == m) {
                temp = akty + k;
                for (int i = akty; i < temp; i++) {
                    C[t[aktx - 1][i]]--;
                    if (!C[t[aktx - 1][i]]) res--;
                    if (!C[t[m][i]]) res++;
                    C[t[m][i]]++;
                }
                sumres += res;
                if (res > maxres) maxres = res;
                akty++;
                if (akty + k - 1 > n) break;
                temp = aktx + k;
                akty--;
                for (int i = aktx; i < temp; i++) {
                    C[t[i][akty]]--;
                    if (!C[t[i][akty]]) res--;
                    if (!C[t[i][akty + k]]) res++;
                    C[t[i][akty + k]]++;
                }
                sumres += res;
                if (res > maxres) maxres = res;
                aktx--;
                akty++;
            } else {
                if (akty & 1) {
                    temp = akty + k;
                    aktx--;
                    for (int i = akty; i < temp; i++) {
                        C[t[aktx][i]]--;
                        if (!C[t[aktx][i]]) res--;
                        if (!C[t[aktx + k][i]]) res++;
                        C[t[aktx + k][i]]++;
                    }
                    sumres += res;
                    if (res > maxres) maxres = res;
                    aktx += 2;
                } else {
                    temp = akty + k;
                    for (int i = akty; i < temp; i++) {
                        C[t[aktx + k][i]]--;
                        if (!C[t[aktx + k][i]]) res--;
                        if (!C[t[aktx][i]]) res++;
                        C[t[aktx][i]]++;
                    }
                    sumres += res;
                    if (res > maxres) maxres = res;
                    aktx--;
                }
            }
        }
    }
    printf("%d %lld", maxres, sumres);
}