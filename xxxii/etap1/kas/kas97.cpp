// Rozwiązanie niedooptymalizowane do zadania 'Kasyno' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: nieistotne w tym zadaniu.
// Złożoność pamięciowa: S P O R A.

#include <bits/stdc++.h>

#include "kaslib.h"
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
using i128 = __int128_t;
using bundle_t = vector<pair<i128, vector<int>>>;
constexpr int MAX_PRIME = 1'000'000;
int SMALL_BUNDLES = 4000;
int sito[10'000'001];
bundle_t small_bundles, big_bundles;

ll R(ll l, ll r) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(l, r)(rng);
}

ll biggest_fitting_power(int p) {
    i128 res = p;
    while (res * p <= DajN()) res *= p;
    return (ll)res;
}

double MULTIPLIER = 3400, SLOPE = 0.26;

vector<ll> hits[50005];
map<int, double> threshold{
{0,9.184861999999997},
{1,11.40034},
{2,12.623819999999991},
{3,13.886899999999997},
{4,14.7189},
{5,15.515719999999998},
{6,16.35482},
{7,17.0481},
{8,17.65326},
{9,18.04936},
{16,19.92754},
{32,24.37019999999998},
{64,29.464779999999998},
{128,31.14732},
{256,41.91064},
{512,43.50824},
{1024,56.3249},
{2048,58.52662},
{99999, 44}
};

double f(int x) { return threshold.upper_bound(x-1)->second; }

vector<ll> zgadniete;
void probuj() {
    i128 n = 1;

    enum SearchStatus { ODPOWIEDZIALEM, SZTURCHLEM, SZUKAJ_DALEJ };
    int x = 1;
    for (auto [b, bundle] : small_bundles) {
        ll B = Pytaj(b);
        for (auto p : bundle) {
            ll g = __gcd((ll)p, B);
            if (g > 1) {
                ll G = Pytaj(biggest_fitting_power(p));
                B *= G / p;
            }
        }
        n *= B;
        if (n * bundle.back() > DajN()) {
            ll m = 1;
            int bundle_id = 1;
            for (auto [b, bundle] : small_bundles) {
                ll B = Pytaj(b);
                for (auto p : bundle) {
                    ll g = __gcd((ll)p, B);
                    if (g > 1) {
                        ll G = Pytaj(biggest_fitting_power(p));
                        B *= G / p;
                    }
                }

                m *= B;
                bundle_id++;
                hits[bundle_id].push_back(m);
            }

            Odpowiedz(n);
            return;
        }

        if (log2((ll)n) < f(x)) {
            Szturchnij();
            return;
        }

        x++;
    }

    Szturchnij();
};

bundle_t make_bundles(vector<int> primes) {
    bundle_t res;
    for (auto p : primes) {
        if (res.empty()) {
            res.push_back({p, {p}});
        } else {
            auto &[b, bundle] = res.back();
            if (b * p <= DajN()) {
                b *= p;
                bundle.push_back(p);
            } else {
                res.push_back({p, {p}});
            }
        }
    }

    return res;
}

int policz() {
    try {
        while (1) {
            probuj();
        }
    } catch (runtime_error e) {
        int wynik = wygrane;
        reset();
        return wynik;
    }

    return wygrane;
}

int32_t main() {
    // cin >> MULTIPLIER >> SLOPE;
    for (int i = 2; i < MAX_PRIME; i++)
        if (!sito[i])
            for (int j = i; j < MAX_PRIME; j += i) sito[j] = i;

    vector<int> primes;
    for (int i = 2; i < MAX_PRIME; i++) {
        if (sito[i] == i) {
            primes.push_back(i);
        }
    }

    auto bundles = make_bundles(primes);

    small_bundles = bundle_t(bundles.begin(), bundles.begin() + SMALL_BUNDLES);

    int hit = policz();

    cout << dbg(hit) << endl;
}
