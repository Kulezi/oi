// Rozwiązanie wolne do zadania 'Zosia' z III etapu XIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((3^(n-k) + k) * (n + m))
// Złożoność pamięciowa: O(k * (n + m))
// Punkty: 50 (upsolve).

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005;
int n, k;

const vector<int> BRAK_WYNIKU = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
vector<int> wynikowy = BRAK_WYNIKU;
vector<int> wyrzucone;

vector<pair<int, int>> usun(vector<pair<int, int>>& e, int x) {
    vector<pair<int, int>> res;
    for (auto [a, b] : e) {
        if (a == x || b == x) continue;
        res.push_back({a, b});
    }

    return res;
}

// Znajduje wszystkie zbiory niezależne.
// k - liczba wierzchołków, które jeszcze mogę usunąć.
void find_iset(int k, vector<pair<int, int>> e) {
    if (e.empty()) {
        if (wyrzucone.size() < wynikowy.size()) wynikowy = wyrzucone;
        return;
    }
    if (k == 0) return;
    auto [a, b] = e.front();

    wyrzucone.push_back(a);

    auto e_a = usun(e, a);
    find_iset(k - 1, usun(e, a));
    wyrzucone.pop_back();

    wyrzucone.push_back(b);
    find_iset(k - 1, usun(e, b));
    wyrzucone.pop_back();

    if (k >= 2) {
        wyrzucone.push_back(a);
        wyrzucone.push_back(b);
        find_iset(k - 2, usun(e_a, b));
        wyrzucone.pop_back();
        wyrzucone.pop_back();
    }
}

int nie_idzie[MAXN];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;

    int m;
    cin >> m;

    vector<pair<int, int>> e;

    while (m--) {
        int a, b;
        cin >> a >> b;
        e.push_back({a, b});
    }

    find_iset(n - k, e);

    if (wynikowy == BRAK_WYNIKU)
        cout << "NIE\n";
    else {
        cout << n - wynikowy.size() << "\n";
        for (auto i : wynikowy) nie_idzie[i] = true;
        for (int i = 1; i <= n; i++) {
            if (!nie_idzie[i]) cout << i << " ";
        }

        cout << "\n";
    }
}