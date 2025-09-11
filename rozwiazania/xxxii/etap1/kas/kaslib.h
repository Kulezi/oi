// Moja biblioteczka do zadania 'Kasyno' z I etapu XXXII OI.
#include <bits/stdc++.h>

using namespace std;
double proby = 0, trafienia = 0;

namespace {
// Można zmienić te wartości.
constexpr long long N = 1'000'000'000'000'000'000ll;
constexpr int POCZATKOWE_BAJTALARY = 10'000'000;
int bajtalary = POCZATKOWE_BAJTALARY;

// Aby zmienić losowość należy zamienić 1 na dowolną inną liczbę typu int.
mt19937_64 rng(2);

long long X;
bool czy_zainicjalizowany = false;
int wygrane = 0, proby = 0;

long long wylosuj_liczbe() {
    proby++;
    // Discard numbers that have factors larger than 10^5.
    // while (1) {
    //     long long x = uniform_int_distribution<long long>(1, N)(rng);
    //     long long y = x;
    //     for (int i = 2; i <= 100'000; i++) {
    //         while (y % i == 0) y /= i;
    //     }

    //     if (y == 1) return x;
    // }
    return uniform_int_distribution<long long>(1, N)(rng);
}

void inicjalizuj_gre() { X = wylosuj_liczbe(); }

void reset() {
    rng = mt19937_64(1);
    czy_zainicjalizowany = 0;
    bajtalary = POCZATKOWE_BAJTALARY;
    wygrane = 0;
}

void inicjalizuj_interakcje() {
    if (czy_zainicjalizowany) return;
    inicjalizuj_gre();
    czy_zainicjalizowany = true;
}

void proba_zakonczenia() {
    if (!bajtalary) {
        int wynik = floor(100.0 * log2(1 + min(2000, wygrane)) / log2(1 + 2000));
        cerr << wynik << "," << wygrane << "," << proby << "," << (double)wygrane / (double)proby
             << endl;
        cerr << "Wynik: " << wygrane << "\n";
        // cerr << "Prób: " << proby << endl;
        cerr << "Trafień: " << wygrane << endl;
        // cerr << "Zapytań na próbę:" << 10'000'000.0 / (double)proby << endl;
        // cerr << "Procent znajdowalnych: " << (double)wygrane / (double)proby << endl;
        // exit(0);
        throw runtime_error("koniec!");
    }
}

void zjedz_bajtalara() {
    proba_zakonczenia();
    --bajtalary;
}
}  // namespace

long long DajN() {
    inicjalizuj_interakcje();
    return N;
}

long long Pytaj(long long y) {
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    proba_zakonczenia();
    return __gcd(X, y);
}

void Szturchnij() {
    inicjalizuj_interakcje();
    zjedz_bajtalara();
    X = wylosuj_liczbe();
    proba_zakonczenia();
}

void Odpowiedz(long long y) {
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    assert(X == y);
    ++wygrane;
    proba_zakonczenia();
    inicjalizuj_gre();
}
