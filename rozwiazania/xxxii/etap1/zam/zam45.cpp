// Rozwiązanie do zadania 'Zamek cykliczny' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(log^2(n))
// Złożoność pamięciowa: O(log(n))
// Punkty: 45 (upsolve)

#include <bits/stdc++.h>
using namespace std;

struct Liczba {
    deque<int> cyfry;
    int operacje;
    Liczba(string n) : operacje(0) {
        for (auto i : n) cyfry.push_back(i - '0');
    }
    void op1() {
        operacje++;
        cyfry.push_back(cyfry.front());
        cyfry.pop_front();
        while (cyfry.front() == 0) cyfry.pop_front();
    }

    void op2() {
        operacje++;
        cyfry.back()++;

        int i = (int)cyfry.size() - 1;
        while (cyfry[i] == 10) {
            cyfry[i] = 0;
            if (i == 0) {
                cyfry.push_front(1);
                break;
            } else
                cyfry[i - 1]++;
            i--;
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    string s;
    cin >> s;

    int wynik = INT_MAX;
    for (int koncowka = 0; koncowka < min(7, (int)s.size()); koncowka++) {
        Liczba n(s);
        while (count(n.cyfry.end() - koncowka, n.cyfry.end(), 9) != koncowka) n.op2();
        while (!(n.cyfry.size() == 1 && n.cyfry.front() == 1)) {
            if (n.cyfry.back() == 0)
                n.op1();
            else if (count(n.cyfry.begin(), n.cyfry.end(), 9) == n.cyfry.size() ||
                     n.cyfry.back() != 9)
                n.op2();
            else
                n.op1();
        }
        wynik = min(wynik, n.operacje);
    }

    cout << wynik << "\n";
}
