#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 1'000'000;
bool bon[MAXN+5], wzieta[MAXN+5];
// pn[k] = pierwsza niesprawdzona jeszcze liczba cukierków podzielna przez k.
int pn[MAXN+5];
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int b;
        cin >> b;
        bon[b] = true;
    }

    cin >> n;

    for (int i = 1; i <= MAXN; i++) 
        pn[i] = i;

    long long nr_klienta = 1;
    vector<long long> boniarze;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        int zostalo = a;
        while (zostalo > 0 && pn[a] <= MAXN) {
            if (!wzieta[pn[a]]) {
                wzieta[pn[a]] = true;
                if (bon[pn[a]])
                    boniarze.push_back(nr_klienta);
                zostalo--;
                nr_klienta++;
            }
            pn[a] += a;
        }

        nr_klienta += zostalo;
    }

    cout << boniarze.size() << "\n";
    for (auto i : boniarze) cout << i << "\n";
}
