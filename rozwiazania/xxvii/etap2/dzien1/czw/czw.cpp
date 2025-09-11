// Rozwiązanie do zadania 'Drzewo czwórkowe' z II etapu XXVII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'005, MOD = 1'000'000'007, INF = 2'000'000'000;
// Znaczy tyle, że ta wartość jest zupełnie nieistotna.
constexpr int _ = -1;
struct Drzewo {
    int id, val, lg, pg, ld, pd, wykladnik;
} t[MAXN];

int rozmiar[MAXN], r[MAXN];
vector<int> zapalone[MAXN];
int ile_spojnych = 0;

int power(int x, int y) {
    int res = 1;
    int pot = x;
    while (y) {
        if (y & 1) res = 1LL * res * pot % MOD;
        pot = 1LL * pot * pot % MOD;
        y >>= 1;
    }

    return res;
}

// Do dzielenia rozmiaru kwadratu przez 4 modulo MOD.
const int INV_4 = power(4, MOD - 2);

string s;
int N = 0;
int buduj(int rozmiar_kwadratu, int wykladnik) {
    int idx = N++;
    if (s[idx] == '0' || s[idx] == '1') {
        t[idx] = Drzewo{idx, s[idx] - '0', _, _, _, _, wykladnik};
        r[idx] = idx;
        rozmiar[idx] = rozmiar_kwadratu;
        if (s[idx] == '1') ile_spojnych++;
    } else {
        // Ćwiartki są 4 razy mniejsze.
        int cwiartka = 1LL * rozmiar_kwadratu * INV_4 % MOD;
        int lg = buduj(cwiartka, wykladnik - 2);
        int pg = buduj(cwiartka, wykladnik - 2);
        int ld = buduj(cwiartka, wykladnik - 2);
        int pd = buduj(cwiartka, wykladnik - 2);
        t[idx] = Drzewo{_, 4, lg, pg, ld, pd, wykladnik};
    }
    return idx;
}

int Find(int x) {
    if (r[x] == x) return x;
    return r[x] = Find(r[x]);
}

// Łączy dwie spójne w jedną licząc rozmiary % MOD.
void Union(int a, int b) {
    int ra = Find(a), rb = Find(b);
    if (r[ra] != r[rb]) {
        rozmiar[ra] += rozmiar[rb];
        rozmiar[ra] %= MOD;
        r[rb] = ra;
        ile_spojnych--;
    }
}

// Lista trzymająca jedynki na aktualnie rozważanej krawędzi.
struct MagicznaLista {
    int wartosc;
    // Wskaźnik na pierwszy i ostatni liść.
    MagicznaLista *pocz, *kon;
    // Wskaźnik na następny liść dla liścia, -1 wpp.
    MagicznaLista *nast;
    // Lewa i prawa połowa krawędzi dla wierzchołka typu 4.
    MagicznaLista *lewa, *prawa;
};

MagicznaLista *lewySyn(MagicznaLista *l) {
    if (l == nullptr) return nullptr;
    if (l->wartosc != -1) return l;
    return l->lewa;
}

MagicznaLista *prawySyn(MagicznaLista *l) {
    if (l == nullptr) return nullptr;
    if (l->wartosc != -1) return l;
    return l->prawa;
}

enum { POZIOME, PIONOWE };
MagicznaLista *lacz(bool kier, int pos, MagicznaLista *lewo) {
    auto &v = t[pos];
    // Zera nas nie interesują...
    MagicznaLista *res = nullptr;
    if (v.val == 1) {
        res = new MagicznaLista{};
        // Będzie O(n) obrotów bo najmniejszy kwadrat ma max 4 sąsiadów, jak się go usunie to
        // następny największy też max 4, itd...
        if (lewo != nullptr) {
            auto ptr = lewo->pocz;
            // Przechodzimy po numerach wszystkich sąsiadujących jedynek na lewo/górę od nas.
            while (ptr != nullptr) {
                Union(ptr->wartosc, v.id);
                if (ptr == lewo->kon) break;
                ptr = ptr->nast;
            }
        }
        res->wartosc = v.id;
        res->pocz = res->kon = res;
        res->nast = nullptr;
        res->lewa = res->prawa = nullptr;
    } else if (v.val == 4) {
        res = new MagicznaLista{};
        res->wartosc = -1;

        if (kier == PIONOWE) {
            res->lewa = lacz(kier, v.lg, lewySyn(lewo));
            res->lewa = lacz(kier, v.pg, res->lewa);
            res->prawa = lacz(kier, v.ld, prawySyn(lewo));
            res->prawa = lacz(kier, v.pd, res->prawa);
        } else {
            res->lewa = lacz(kier, v.lg, lewySyn(lewo));
            res->lewa = lacz(kier, v.ld, res->lewa);
            res->prawa = lacz(kier, v.pg, prawySyn(lewo));
            res->prawa = lacz(kier, v.pd, res->prawa);
        }

        if (res->lewa == nullptr && res->prawa == nullptr)
            return nullptr;
        else if (res->prawa == nullptr) {
            res->pocz = res->lewa->pocz;
            res->kon = res->lewa->kon;
        } else if (res->lewa == nullptr) {
            res->pocz = res->prawa->pocz;
            res->kon = res->prawa->kon;
        } else {
            res->pocz = res->lewa->pocz;
            res->kon = res->prawa->kon;
        }

        if (res->lewa != nullptr && res->lewa->kon != nullptr && res->prawa != nullptr)
            res->lewa->kon->nast = res->prawa->pocz;
    }

    return res;
}

vector<int> najwiekszy;
int najwiekszy_rozmiar;

int32_t main() {
    int n;
    cin >> n;
    cin >> s;

    buduj(power(4, n), INF);

    vector<int> lewo, prawo, gora, dol;
    lacz(PIONOWE, 0, nullptr);
    lacz(POZIOME, 0, nullptr);

    // Teraz zostało jeszcze tylko dowiedzieć się, która ze spójnych jest największa.
    for (int i = 0; i < N; i++) {
        if (t[i].val != 1) continue;
        int ri = Find(i);
        zapalone[ri].push_back(t[i].wykladnik);
    }

    // Dla każdej spójnej wyliczamy jej faktyczny rozmiar jako liczbę binarną.
    for (int i = 0; i < N; i++) {
        // Liczbę reprezentujemy jako listę zapalonych bitów, bo jest za długa na standardowa
        // reprezentację.
        auto &z = zapalone[i];
        if (z.empty()) continue;
        sort(z.begin(), z.end(), [&](int a, int b) { return a > b; });

        // Żeby porównywać to każda potęga może występować max raz, więc zliczamy ich wystąpienia.
        vector<pair<int, int>> ile_danej_potegi;
        int last = z[0], cnt = 0;
        for (auto wyk : z) {
            if (last == wyk) {
                cnt++;
            } else {
                ile_danej_potegi.emplace_back(last, cnt);
                last = wyk;
                cnt = 1;
            }
        }
        ile_danej_potegi.emplace_back(last, cnt);

        // I wymieniamy każde dwie kopie 2 ^ x na jedną kopię 2 ^ { x + 1 }, aż będzie git.
        vector<int> ostateczny;
        while (!ile_danej_potegi.empty()) {
            auto [wyk, ile] = ile_danej_potegi.back();
            ile_danej_potegi.pop_back();
            if (ile > 1) {
                if (!ile_danej_potegi.empty() && ile_danej_potegi.back().first == wyk + 1) {
                    ile_danej_potegi.back().second += ile / 2;
                } else {
                    ile_danej_potegi.emplace_back(wyk + 1, ile / 2);
                }
            }

            if (ile % 2 == 1) ostateczny.push_back(wyk);
        }

        reverse(ostateczny.begin(), ostateczny.end());
        // Tu zrobimy O(n) porównań bo każdy bit nienajwiększego rozmiaru porównamy conajwyżej raz.
        if (ostateczny > najwiekszy) {
            najwiekszy = ostateczny;
            najwiekszy_rozmiar = rozmiar[i];
        }
    }

    cout << ile_spojnych << "\n";
    cout << najwiekszy_rozmiar << "\n";
}
