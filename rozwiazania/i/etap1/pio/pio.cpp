// Rozwiązanie do zadania 'Pionki' z I etapu I OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((liczba pól)^3)
// Złożoność pamięciowa: O((liczba pól)^3)
// Punkty: 100 (upsolve)

#include <array>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
constexpr int L = 8, N = L * L;
enum {
    CZARNY,
    BIALY,
};

int id(int x, int y) { return x * L + y; }
int dx[L] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[L] = {-1, 0, 1, -1, 1, -1, 0, 1};
array<int, N> C;

vector<int> rozwiaz(int kolor) {
    // Działamy mod 2.
    // C + Ax = M
    // Ax = (M + C) -> M := M + C
    // Rozwiązujemy układ Ax = M eliminacją gaussa.
    
    // Wyznaczamy M.
    array<int, N> M = C;
    for (auto &i : M) i = i ^ kolor;

    // Wyznaczamy A.
    array<array<int, N>, N> A = {{}};
    for (int x = 0; x < L; x++) {
        for (int y = 0; y < L; y++) {
            for (int d = 0; d < L; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= L || ny < 0 || ny >= L) continue;
                A[id(x, y)][id(nx, ny)] = 1;
            }
        }
    }

    // Schodkujemy A.
    for (int i = 0; i < N; i++) {
        // Wybieramy wiersz, który będzie i-tym.
        int m = i;
        for (int j = i + 1; j < N; j++)
            if (A[m][i] < A[j][i]) m = j;

        for (int j = 0; j < N; j++) swap(A[m][j], A[i][j]);
        swap(M[m], M[i]);

        // Odejmujemy go od niższych.
        for (int j = i + 1; j < N; j++) {
            if (!A[j][i]) continue;
            for (int k = i; k < N; k++) A[j][k] ^= A[i][k];
            M[j] ^= M[i];
        }
    }

    vector<int> res;
    // Podstawiamy od najniższego wiersza.
    for (int i = N - 1; i >= 0; i--) {
        if (M[i]) res.push_back(i + 1);
        // Zerujemy i-te kolumny w wyższych wierszach odejmując.
        for (int j = i - 1; j >= 0; j--) {
            if (A[j][i]) {
                A[j][i] = 0;
                M[j] ^= M[i];
            }
        }
    }

    return res;
}

int32_t main() {
    // Pole jest koloru takiego samego jak na wejściu
    // wtw. gdy sąsiedzi zostali kliknięci parzyście wiele razy.
    // => Każde optymalne rozwiązanie wykonuje po max 1 operacji na pole.
    // => Kolejność operacji nie ma znaczenia.

    // Załóżmy teraz, że chcemy pokolorować planszę na biało.
    // Żeby lewy górny róg był biały mamy dwa przypadki:
    // Już jest biały - albo nie ruszamy w ogóle sąsiadów
    // albo wykonujemy ruch na dwóch z nich (oboje na siebie wpłyną zmieniając sobie kolor).

    for (int i = 0; i < L; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < L; j++) {
            C[id(i, j)] = (s[j] == 'C' ? CZARNY : BIALY);
        }
    }

    // Czarna plansza.
    auto czarna = rozwiaz(CZARNY);
    // Biała plansza.
    auto biala = rozwiaz(BIALY);

    cout << min(czarna.size(), biala.size()) << endl;
    if (czarna.size() < biala.size()) {
        for (auto i : czarna) cout << i << " ";
    } else {
        for (auto i : biala) cout << i << " ";
    }

    cout << "\n";
}