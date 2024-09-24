// Rozwiązanie do zadania 'Trójkąty' z I etapu I OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(1)
// Punkty: 100 (upsolve)

#include <cstdio>
// Maksymalna wartość występująca w mianowniku/liczniku ułamka z wejścia.
constexpr int M = 9999;

// Liczba wymierna postaci p/q.
struct Wymierna {
    long long p, q;

    bool operator<(Wymierna &rhs) {
        return p * rhs.q < rhs.p * q;
    }

    bool operator>(Wymierna &rhs) {
        return p * rhs.q > rhs.p * q;
    }

    Wymierna operator+(Wymierna rhs) {
        return {p * rhs.q + q * rhs.p, q * rhs.q};
    }
    
};

int main() {
    int n;
    scanf("%d", &n);

    Wymierna najmniejsza, druga_najmniejsza, najwieksza;
    najmniejsza = druga_najmniejsza = {M, 1};
    najwieksza = {1, M};
    for (int i = 1; i <= n; i++) {
        int p, q;
        scanf("%d/%d", &p, &q);
        Wymierna dlugosc = {p, q};
        if (dlugosc < najmniejsza) {
            druga_najmniejsza = najmniejsza;
            najmniejsza = dlugosc;
        } else if (dlugosc < druga_najmniejsza) {
            druga_najmniejsza = dlugosc;
        }

        if (najwieksza < dlugosc) {
            najwieksza = dlugosc;
        }
    }

    if (najmniejsza + druga_najmniejsza > najwieksza) {
        puts("TAK");
    } else {
        puts("NIE");
    }
}