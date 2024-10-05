// Biblioteczka testowa do zadania 'Gdzie jest jedynka?' z III etapu XX OI.
// Autor: Paweł Putra

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#define all(v) (v).begin(), (v).end()
using namespace std;
namespace {
vector<int> perm;
int n;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

bool in_range(int i) { return i >= 1 && i <= n; }
}  // namespace

int inicjuj() {
    n = R(1, 100000);
    perm = vector<int>(n);
    cerr << "n = " << n << "\n";
    iota(all(perm), 1);
    random_shuffle(all(perm));
    cerr << "[" << perm[0];
    for (int i = 1; i < n; i++) cerr << ", " << perm[i];
    cerr << "]\n";
    return n;
}

int q;
int f(int i, int j, int d) {
    q++;
    cerr << __func__ << "(" << i << "," << j << "," << d << ") = ";
    assert(in_range(i));
    assert(in_range(j));
    assert(in_range(d));
    int a_i = perm[i - 1];
    int a_j = perm[j - 1];
    int res = abs(a_i - a_j) % d == 0;
    cerr << res << "\n";
    return res;
}

int g(int i, int j) {
    assert(in_range(i));
    assert(in_range(j));
    cerr << __func__ << "(" << i << "," << j << ") = ";
    int a_i = perm[i - 1];
    int a_j = perm[j - 1];
    cerr << (a_i > a_j ? 1 : 0) << "\n";
    return a_i > a_j;
}

void odpowiedz(int k) {
    cerr << __func__ << "(" << k << ")\n";
    if (perm[k - 1] == 1) {
        cout << "Good guess!\n";
        cout << q / n << "\n";
        exit(0);
    } else {
        cout << "Bad guess!\n";
        exit(1);
    }
}