// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    int wynik = 0;

    vector<int> stos;
    for (int i = 1; i <= n; i++) {
        int d, w;
        cin >> d >> w; 
        
        while (!stos.empty() && stos.back() > w) {
            wynik++;
            stos.pop_back();
        }
        
        if (stos.empty() || stos.back() < w)
            stos.push_back(w);
    }

    cout << wynik + stos.size() << "\n";
}