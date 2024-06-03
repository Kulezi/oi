#include <bits/stdc++.h>
using namespace std;

void solve(int tc) {
    int k;
    cin >> k;

    vector<int> len(k);
    vector<string> podstawienie(k);
    for (int i = 0; i < k; i++) {
        cin >> len[i];

        podstawienie[i] = string(len[i], 'a');
    }

    array<string, 2> s;
    for (int eq = 0; eq < 2; eq++) {
        int l;
        cin >> l;
        
        cin >> s[eq];
    }

    // I tak sie nie zmiesci, ale i tak licze w O(wynik), wiec wiecej niz 10^18 i tak nie przetestuje tym.
    long long res = 0;
    auto dolicz = [&]() {
        array<string, 2> podstawione;
        for (int eq = 0; eq < 2; eq++) {
            for (int i = 0; i < s[eq].size(); i++) {
                if (s[eq][i] == '0' || s[eq][i] == '1') podstawione[eq] += s[eq][i];
                else podstawione[eq] += podstawienie[s[eq][i]-'a'];
            }
        }

        if (podstawione[0] == podstawione[1]) {
            res++;
            
            cerr << "lhs = rhs = [" << podstawione[1] << "]\n";
            for (int i = 0; i < k; i++) cerr << (char)(i+'a') << " = [" << podstawienie[i] << "]\n";
            cerr << "\n";
        }
    };

    // Sprawdza wszystkie podstawienia zmiennych x_1, ..., x_k.
    auto podstaw = [&](int slowo, int ktora_literka, int jaka_literka, auto &&self) {
        podstawienie[slowo][ktora_literka] = jaka_literka;
        int nastepne_slowo = slowo;
        int nastepna_literka = ktora_literka + 1;
        if (nastepna_literka == len[slowo]) {
            if (slowo == k-1) {
                dolicz();
                return;
            }

            nastepne_slowo++;
            nastepna_literka = 0;
        }

        self(nastepne_slowo, nastepna_literka, '0', self);
        self(nastepne_slowo, nastepna_literka, '1', self);
    };

    podstaw(0, 0, '0', podstaw);
    podstaw(0, 0, '1', podstaw);

    cout << res << "\n";
}

int32_t main() {
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
}