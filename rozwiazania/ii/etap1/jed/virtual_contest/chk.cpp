#include <bits/stdc++.h>
using namespace std;

void validate(string name, string sol, int n) {
    if (sol == "BRAK") return;
    if (sol.size() > 100) {
        cerr << name << ": solution size too big (" << sol.size() << " > 100)\n";
        return;
    }

    int reszta = 0;
    for (auto i : sol) {
        reszta *= 10;
        if (i == '1') reszta++;
        reszta %= n;
    }

    if (reszta != 0) {
        cerr << name << ": solution has wrong remainder (" << reszta << " != 0)\n";
        return;
    }
}

int32_t main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    
    if (argc != 4) {
        cerr << "usage ./chk test.in brute.out model.out\n";
        exit(1);
    }

    ifstream test(argv[1]), brut(argv[2]), model(argv[3]);

    int tests;
    test >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        int n;
        test >> n;

        string n_brute, n_model;
        brut >> n_brute;
        model >> n_model;

        validate("brute", n_brute, n);
        validate("model", n_model, n);

        if (n_brute == "BRAK" && n_model != "BRAK") {
            cerr << "brute didn't find solution and model did for n = " << n << "\n";
            return 1;
        }

        if (n_brute != "BRAK" && n_model == "BRAK") {
            cerr << "model didn't find solution and brute did for n = " << n << "\n";
            return 1;
        }
    }
}