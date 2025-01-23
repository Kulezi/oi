// Rozwiązanie do zadania 'Zamek cykliczny' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(log(n))
// Złożoność pamięciowa: O(log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
struct Liczba {
    deque<int> cyfry;
    int ops;
    int ile_niedziewiatek;
    Liczba(string n) : ops(0), ile_niedziewiatek(0) {
        for (auto i : n) {
            cyfry.push_back(i - '0');
            if (i != '9') ++ile_niedziewiatek;
        }
    }
    void op1() {
        ++ops;
        cyfry.push_back(cyfry.front());
        cyfry.pop_front();
        while (cyfry.front() == 0) {
            cyfry.pop_front();
            --ile_niedziewiatek;
        }
    }

    void op2() {
        ++ops;
        ++cyfry.back();
        if (cyfry.back() == 9) --ile_niedziewiatek;

        // Przepychamy jedynkę w lewo.
        for (int i = (int)cyfry.size() - 1; cyfry[i] == 10; i--) {
            cyfry[i] = 0;
            ++ile_niedziewiatek;
            if (i == 0) {
                cyfry.push_front(1);
                ++ile_niedziewiatek;
                break;
            } else {
                cyfry[i - 1]++;
                if (cyfry[i - 1] == 9) --ile_niedziewiatek;
            }
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    string s;
    cin >> s;

    int wynik = INT_MAX;

    // Wynik nie przekracza 10 * długość liczby -> wystarczy max 7 ostatnich cyfr zmienić na
    // dziewiątki na początku. To żeby obłużyć takie przypadki jak np.
    // 9999999999999999999999999999999999999999999999999999999989.
    for (int koncowka = 0; koncowka < min(7, (int)s.size()); koncowka++) {
        Liczba n(s);
        while (count(n.cyfry.end() - koncowka, n.cyfry.end(), 9) != koncowka) n.op2();

        while (!(n.cyfry.size() == 1 && n.cyfry.front() == 1)) {
            // Do zera nie opłaca się dodawać, bo i tak musimy z niego potem zrobić zero żeby
            // znikło.
            if (n.cyfry.back() == 0) n.op1();
            // Jak mamy 9 na końcu albo nasza liczba już jest samymi dziewiątkami to chcemy dodać
            else if (!n.ile_niedziewiatek || n.cyfry.back() != 9)
                n.op2();
            else
                n.op1();
        }

        wynik = min(wynik, n.ops);
    }

    cout << wynik << "\n";
}