// Biblioteczka testowa z rozwiązaniem brutalnym do zadania 'Architekci' z II etapu XVI OI.
// Autor: Paweł Putra

#ifndef ARC_H
#define ARC_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
namespace {
using namespace std;
constexpr int MAX_A = 1'000'000'000;
int n, k, cur_idx;
bool koniec;
vector<int> projekty, ans, odp;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

}  // namespace

int inicjuj() {
    n = R(1, 10000);
    k = R(1, 1);
    cerr << "n = " << n << ", k = " << k << endl;
    cur_idx = 0;
    koniec = false;

    projekty = ans = odp = vector<int>();
    for (int i = 0; i < n; i++) projekty.push_back(R(1, MAX_A));
    cerr << "[" << projekty[0];
    for (int i = 1; i < n; i++) cerr << ", " << projekty[i];
    cerr << "]\n";

    // Brutalne szukanie wyniku w O(k * n).
    int szukaj_od = 0;
    for (int zostalo = k - 1; zostalo >= 0; zostalo--) {
        // Chcemy najlepszy projekt, ale musi nam zostać zostalo-1 projektów po nim.
        auto it = max_element(projekty.begin() + szukaj_od, projekty.end() - zostalo);
        ans.push_back(*it);
        szukaj_od = it - projekty.begin() + 1;
    }

    return k;
}

int wczytaj() {
    cerr << __func__ << "()" << endl;
    if (koniec) {
        cout << __func__ << "() wywołane po wczytaniu całego ciągu!";
        exit(1);
    }
    if (cur_idx == projekty.size()) return 0;
    return projekty[cur_idx++];
}

void wypisz(int x) {
    cerr << __func__ << "(" << x << ")" << endl;
    odp.push_back(x);
    if (odp.size() > k) {
        cout << "wywołano wypisz() więcej niż k razy!";
        exit(1);
    }

    if (odp.size() == k) {
        if (odp == ans)
            cout << "OK\n";
        else {
            cout << "Błędna odpowiedź!";
            exit(1);
        }
    }
}

#endif  // ARC_H