// Generatorka testów do zadania 'Sprawiedliwy podział' z I etapu XXXII OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
int n;
vector<int> a, b;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

constexpr int MAX_A = 10, MAX_B = MAX_A, MAX_N = 5;

int32_t main() {
    ios_base::sync_with_stdio(0);
    // Jak się wylosuje coś co nie ma prawa działać to po prostu losujemy od nowa.
    for (;;) {
        n = R(1, MAX_N);
        // Wygeneruj ciąg będący jedną z działających odpowiedzi.
        vector<int> sol(n);
        for (auto &i : sol) i = R(0, 1);

        a = vector<int>(n, 0), b = vector<int>(n, 0);

        // Wygeneruj losowo elementy, które wliczają się do sumy danej osoby.
        ll sum_a = 0, sum_b = 0;
        int rem_a = n, rem_b = n;
        for (int i = 0; i < n; i++) {
            if (sol[i] == 0) {
                a[i] = R(1, MAX_A);
                sum_a += a[i];
                rem_a--;
            } else {
                b[i] = R(1, MAX_B);
                sum_b += b[i];
                rem_b--;
            }
        }

        int idx_min_a = (rem_a == 0 ? 0 : R(1, rem_a));
        int idx_min_b = (rem_b == 0 ? 0 : R(1, rem_b));

        int min_a = 0;
        int min_b = 0;
        if (rem_a == 1)
            min_a = R(1, MAX_A);
        else if (rem_a > 1) {
            if (sum_a < rem_a - 1) continue;
            min_a = R(1, sum_a / (rem_a - 1));
        }

        if (rem_b == 1)
            min_b = R(1, MAX_B);
        else if (rem_b > 1) {
            if (sum_b < rem_b - 1) continue;
            min_b = R(1, sum_b / (rem_b - 1));
        }

        // Każdy dostanie minimalnie minimum więc odejmij od sumy.
        sum_a -= min_a * rem_a;
        sum_b -= min_b * rem_b;

        // Minimum będzie odjęte, więc można o tyle więcej rozdać po innych elementach.
        sum_a += min_a;
        sum_b += min_b;

        // Rozdystrybuuj pozostałą sumę tak, żeby nadal było git.
        for (int i = 0; i < n; i++) {
            // Z prawdopodobieństwem 50% zrób tak, żeby suma faktycznie wychodziła równa, bo to się
            // będzie bardzo rzadko dziać dla dużych MAX_A.
            if (sol[i] == 0) {
                if (rem_b == idx_min_b) {
                    b[i] = min_b;
                } else {
                    b[i] = min_b + R(0, sum_b);
                    if (rem_b == 1 && R(0, 1)) b[i] = min_b + sum_b;
                    sum_b -= b[i] - min_b;
                }

                rem_b--;
            } else {
                if (rem_a == idx_min_a) {
                    a[i] = min_a;
                } else {
                    a[i] = min_a + R(0, sum_a);
                    if (rem_a == 1 && R(0, 1)) a[i] = min_a + sum_a;
                    sum_a -= a[i] - min_a;
                }

                rem_a--;
            }
        }

        break;
    }

    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << "\n";
}