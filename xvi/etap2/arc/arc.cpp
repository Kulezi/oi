// Rozwiązanie do zadania 'Architekci' z II etapu XVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(k)
// Punkty: 100 (upsolve)

#include "arc.h"

#include <deque>
using namespace std;
int main() {
    int k = inicjuj();
    deque<int> koncowka;
    while (koncowka.size() < k) {
        koncowka.push_back(wczytaj());
    }

    // Kolejka maksimów utrzymująca ciąg elementów, które jeszcze mogą być największym.
    deque<int> dq;
    auto dodaj = [&](int x) {
        while (!dq.empty() && x > dq.back()) dq.pop_back();
        dq.push_back(x);
    };

    auto wyjmij = [&]() {
        int x = dq.front();
        dq.pop_front();
        return x;
    };
    
    // Tylko dla k ostatnich elementów możemy wziąć coś co nie jest w kolejce.
    for (int projekt = wczytaj(); projekt != 0; projekt = wczytaj()) {
        koncowka.push_back(projekt);
        auto przerzucany = koncowka.front();
        koncowka.pop_front();
        dodaj(przerzucany);
    }

    // Bierzemy jak najwcześniejszy najlepszy projekt, ale musi po nim zostać tyle,
    // żeby nadal dało się uzbierać k projektów.
    for (auto przerzucany : koncowka) {
        dodaj(przerzucany);
        wypisz(wyjmij());
    }
}