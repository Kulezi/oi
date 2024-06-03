// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * |A|)
// Punkty: 100 (upsolve).

// Szukanie cyklu w grafie podsłów, podwójne haszowanie do zliczania i porównywania podsłów długości k.
// Rozwiązanie użyte na warsztatach z testowania, linijki opatrzone znacznikiem BUG, mówią co mogło w niej pójść nie tak.
#include <bits/stdc++.h>
using namespace std;
using Hash = pair<int, int>;

constexpr int B[2] = {31, 69}, ILE_HASZY = 2; /// BUG: ups. baza w haszowaniu mniejsza od alfabetu -> nie odróżnimy 'a' od 'a' + 23.
constexpr int MOD[2] = {1'000'000'009, 1'000'69'69'69}; /// BUG: ojejku, to nie sa liczby pierwsze.

int main() {
    ios_base::sync_with_stdio(0);       /// BUG: Nie ma magicznej linijki -> bedzie za wolne.
    long long n, k, a, b;                     /// BUG: input się przekręci.
    cin >> n >> k >> a >> b;

    string s;
    cin >> s;

    assert(n >= 2);
    assert(n <= 1'000'000);
    assert(n < a);
    assert(a < b);
    assert(b + 1 - a <= 1'000'000);
    assert(b <= (long long)1e18);

    string wynik;
    map<Hash, map<char, int>> ile;      // Trzyma ile razy wystąpiła literka po takim słowie długości k.
    map<Hash, char> najczestsza;        // Trzyma najczęściej występującą literkę po takim słowie.

    auto nastepna = [&](Hash &substring) {
        char p = najczestsza[substring];
        if (p == 0) p = 'a';
        return p;
    };

    // Trzyma B do potegi k-tej z haszowania.
    int B_k[2] = {1, 1};

    // Trzyma hasze okienka długości k.
    int okienko[2] = {0, 0};

    // Na początku kolejki stoi literka, która następna wyleci z okienka.
    queue<int> q;
    
    // Wylicz hasze pierwszego okienka.
    for (int i = 1; i <= k; i++) {
        q.push(s[i-1] - 'a' + 1); 

        for (int j = 0; j < ILE_HASZY; j++) {
            B_k[j] = 1LL * B_k[j] * B[j] % MOD[j];                              /// BUG: ups, pokićkałem indeksy
            okienko[j] = (1LL * okienko[j] * B[j] + s[i-1] - 'a' + 1) % MOD[j]; /// BUG: ^ ditto.
        }
    }

    Hash H = {okienko[0], okienko[1]};

    // Usuwa literkę z początku słowa i dopisuje literkę c.
    auto przesun_okienko = [&](char c) {
        int d = q.front();
        q.pop();
        
        for (int j = 0; j < ILE_HASZY; j++) {
            okienko[j] = (1LL * okienko[j] * B[j] + c - 'a' + 1) % MOD[j]; /// BUG: Ups przekręca się, można np. pomnozyć przez 1LL z lewej strony.
            okienko[j] -= 1LL * d * B_k[j] % MOD[j];                       /// BUG: ^ ditto.
            okienko[j] %= MOD[j];
           
            if (okienko[j] < 0) okienko[j] += MOD[j];   /// BUG: <- ojejku, zapomniałem o ujemnym modulo.
        }
        
        H = {okienko[0], okienko[1]};
        q.push(c - 'a' + 1);
    };

    // Przesuwamy okienko po wejsciowym słowie zliczając wystąpienia liter po nim.
    for (int i = 1; i + k <= n; i++) {
        char c = s[i+k-1];
        ile[H][c]++;
        char best = nastepna(H);
        if (ile[H][c] > ile[H][best] || (ile[H][c] == ile[H][best] && best > c)) najczestsza[H] = c; /// BUG: ups, zepsułem nawiasowanie.
        przesun_okienko(c);
    }

    // Przedłuża słowo o jedną predykcję z zadania.
    auto przedluz = [&]() -> char {
        char c = nastepna(H);
        n++;
        przesun_okienko(c);

        // Jak literka jest w przedziale [a, b] to dopisz do wyniku.
        if (n >= a && n <= b) wynik += c;
        return c;
    };

    map<Hash, int> vis;

    // Trzyma literki, które będą po wyjściowym słowie.
    string kontynuacja;
    while (!vis[H]) {
        vis[H] = kontynuacja.size();
        kontynuacja += przedluz();
    }

    string cycle = kontynuacja.substr(vis[H]);
    long long cycle_size = cycle.size(); /// BUG: to musi być long longiem.

    // Pierwsze przejscie zebraliśmy całe, eraz trzeba tylko chodzić po cyklu.
    // Ignorujemy te przejścia po cyklu, które nie będą w wyniku.
    n += max(0LL, (a - 1 - n)) / cycle_size * cycle_size; /// BUG: to się przekręci jak nic nie będzie long longiem.

    // Teraz zostało nam już tylko ~milion literek do przejścia to dopisujemy na pałę.
    while (n < b) {
        przedluz();
    }

    cout << wynik << "\n";
}