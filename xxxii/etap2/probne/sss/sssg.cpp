// Generatorka testów do zadania 'Sekretna siatka szpiegowska' z XXXII OI"
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int SUBTASK = 1;
constexpr int K[4] = {50, 20, 15, 10};
constexpr int T[4] = {50, 100, 100, 100};
constexpr int N[4] = {500, 800, 100000, 200000};
constexpr int S[4] = {(int)1e9, (int)1e9, (int)2e6, (int)2e6};

void gen_tree(int n) {
    cout << n << " " << K[SUBTASK] << "\n";
    for (int i = 2; i <= n; i++) {
        cout << R(1, i-1) << " " <<  i << "\n";
    }
}

int main() {
    cin >> SUBTASK;

    int t = T[SUBTASK];
    cout << t << endl;
    for (int rem = t-1; rem >= 0; rem--) {
        int n = R(max(1, N[SUBTASK] / 100), N[SUBTASK]);
        gen_tree(n);
    }
}
