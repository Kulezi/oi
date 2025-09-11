// Rozwiązanie alternatywne do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * log^2(q)) z bardzo niską stałą :)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

// Rozwiązanie w 100% polega na przyśpieszaniu naiwnego bruta przy pomocy Heavy-Light Decomposition.
// Pod kodem jest spisane pełne omówienie rozwiązania, potrzebowałem je spisać przed implementacją,
// bo się pogubiłem.

#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_Q = 1'000'005;

// Wszystko co potrzebne damy radę upchnąć w czterech fenwickach.
// Da się mniej, ale szkoda zachodu.
struct Fenwick {
    int fw[MAX_Q];
    void add_point(int x, int delta) {
        for (; x < MAX_Q; x |= x + 1) fw[x] += delta;
    }

    void add_range(int l, int r, int delta) {
        add_point(l, delta);
        add_point(r + 1, -delta);
    }

    int sum(int r) {
        int res = 0;
        for (; r > 0; r = (r & (r + 1)) - 1) res += fw[r];
        return res;
    }

    int sum(int l, int r) { return sum(r) - sum(l - 1); }
} jealous_node_fw, picky_node_fw, jealous_path_fw, picky_path_fw;

int q;
pair<char, int> queries[MAX_Q];

vector<int> g[MAX_Q];
int par[MAX_Q], r[MAX_Q];
bool is_jealous[MAX_Q];

// Do przypadków 3 i 4.
int picky_sons[MAX_Q], initial[MAX_Q], jealous_children[MAX_Q];

// Do indeksowania Fenwicków wierzchołków.
int son_id[MAX_Q], lson[MAX_Q], rson[MAX_Q];

// Do HLD.
int in[MAX_Q], sub[MAX_Q], head[MAX_Q];
int path_start(int v) { return in[g[head[v]][0]]; }
void add_edge(int src, int dst, char typ) {
    g[src].push_back(dst);
    par[dst] = src;
    r[dst] = dst;
    if (typ == 'Z') {
        r[dst] = r[src];
        is_jealous[dst] = true;
    }
}


// Insert dla przypadku 1.
void clone_jealous(int v) {
    while (head[v] != head[r[v]]) {
		// Wliczamy całość przecięcia z ciężką ścieżką naraz.
        if (v != head[v]) {
            jealous_path_fw.add_range(path_start(v), in[v], 1);
            v = head[v];
        }

		// Wliczamy lekką krawędź, przeskakując na kolejną ciężką ścieżkę.
        jealous_node_fw.add_point(son_id[v], 1);
        v = par[v];
    }

	// Potencjalnie została nam jeszcze ostatnia ciężka ścieżka do policzenia.
    if (v != r[v]) {
        int heavy_son = g[r[v]][0];
        jealous_path_fw.add_range(in[heavy_son], in[v], 1);
    }
}

// Zapytanie dla przypadku 1.
int cloned_jealous(int u) {
    int p = par[r[u]];
    if (!p) return 0;

    int res = 0;

    // Lekkie krawędzie.
    res += jealous_node_fw.sum(son_id[r[u]], rson[p]);

    // Ciężka krawędź (o ile istnieje).
    int heavy_son = g[p][0];
    if (heavy_son > r[u]) res += jealous_path_fw.sum(in[heavy_son]);
    return res;
}

// Insert dla przypadku 2.
void clone_picky(int v) {
    int p = par[r[v]];
    if (!p) return;

    // To będę czytał tylko lekkimi krawędźmi.
    picky_node_fw.add_point(son_id[r[v]], 1);

    // A to ciężkimi.
    int heavy_son = g[p][0];
    if (r[v] < heavy_son) picky_path_fw.add_point(in[heavy_son], 1);
}

// Zapytanie dla przypadku 2.
int cloned_picky(int u) {
    int res = 0;
    while (head[u] != head[r[u]]) {
		// Wliczamy całość przecięcia z ciężką ścieżką naraz.
        if (u != head[u]) {
            res += picky_path_fw.sum(path_start(u), in[u]);
            u = head[u];
        }

		// Wliczamy lekką krawędź, przeskakując na kolejną ciężką ścieżkę.
        res += picky_node_fw.sum(lson[par[u]], son_id[u]);
        u = par[u];
    }

	// Potencjalnie została nam jeszcze ostatnia ciężka ścieżka do policzenia.
    if (u != r[u]) {
        int heavy_son = g[r[u]][0];
        res += picky_path_fw.sum(in[heavy_son], in[u]);
    }

    return res;
}

int deg(int v) {
    return initial[v] + picky_sons[v] + cloned_picky(v) + cloned_jealous(v) +
           jealous_children[v];
}

void assign_ranges() {
    // Zamiast trzymać oddzielne drzewo dla każdego wierzchołka, zrobimy jedno.
    // Indeksy synów jednego typu dla jakiegoś u będą tworzyć przedział,
    // zapamiętamy też jaki numer ma dany syn.
    int M = 0;

    for (int u = 1; u <= q; u++) {
        lson[u] = MAX_Q;
        for (auto v : g[u]) {
            son_id[v] = ++M;
            rson[u] = M;
            lson[u] = min(lson[u], M);
        }
    }
}

// Przestawia najcięższych synów na początek listy sąsiedztwa,
// Dzięki temu ciężkie ścieżki zawsze mają spójny przedział preorderów,
// pozwalając używać jednego drzewa zamiast oddzielnego dla każdej ze ścieżek.
int reorder(int v) {
    sub[v] = 1;
    for (auto &u : g[v]) {
        sub[v] += reorder(u);
        if (sub[u] > sub[g[v][0]]) swap(u, g[v][0]);
    }

    return sub[v];
}

// Wyznaczamy dla każdego wierzchołka kto jest na samej górze jego ciężkiej ścieżki.
int T;
void hld(int u) {
    in[u] = ++T;
    for (auto v : g[u]) {
        if (v == g[u][0])
            head[v] = head[u];
        else
            head[v] = v;
        hld(v);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> q;

    r[1] = 1;
    add_edge(1, 2, 'W');
    for (int i = 1, t = 2; i <= q; i++) {
        auto &[typ, v] = queries[i];
        cin >> typ >> v;

        if (typ == 'W' || typ == 'Z') {
            ++t;
            add_edge(v, t, typ);
        } else {
			// W razie gdybym zbugował generatorkę :)
            assert(typ == '?');
        }
    }

    assign_ranges();
    reorder(1);
    hld(1);

    queries[0] = {'W', 1};
    for (int i = 0, t = 1; i <= q; i++) {
        auto &[typ, v] = queries[i];
        if (typ == 'W') {
            ++t;
            ++picky_sons[v];
            initial[t] = 1 - deg(t);
        } else if (typ == 'Z') {
            t++;
            initial[t] = deg(v) - deg(t);
            clone_jealous(t);
            clone_picky(t);
            jealous_children[par[r[v]]]++;
        } else {
            cout << deg(v) << endl;
        }
    }
}


// Omówienie (napisałem przed implementacją):
// Przez deg(v) oznaczmy stopień wierzchołka (vertex degree).

// Gdy wprowadzamy wierzchołek t, to:
// 1. Jeśli t jest wybredny względem wierzchołka v, sprawa jest prosta.
// Ustawiamy deg(t) := 1, i deg(v) := deg(v) + 1
// 2. Jeśli t jest zazdrosny względem wierzchołka v, sprawa się nieco komplikuje.
// Oczywiście deg(t) := deg(v), ale trzeba jeszcze uwzględnić wierzchołek t w stopniach wierzchołków sąsiadujących z v.
// Innymi słowy ustawić deg(u) := deg(u) + 1, dla każdego sąsiada v.
//
// Żeby zobrazować sobie kim mogą być ci sąsiedzi, narysujemy drzewo, które odpowiada zapytaniom z wejścia.
// Nie możemy wszak rozrysować całego grafu - bo może mieć O(q^2) krawędzi, co już zepsułoby nam złożoność.
// Drzewo będzie ukorzenione w wierzchołku numer 1. Każdy wierzchołek t z wejścia ma jako ojca w drzewie
// wierzchołek względem którego jest zazdrosny bądź wybredny. Krawędzie tych wybrednych narysujemy jak zwykłą krawędź,
// a te zazdrosnych będą strzałką w stronę ojca - bo po nim kopiują. 
//
// Popatrzmy na najdłuższą ścieżkę P z samych strzałkowych krawędzi idącą w górę z wierzchołka v,
// nazwijmy ją P(v), a jako r(v) oznaczmy najwyższy wierzchołek na tej ścieżce.
// Zauważmy, że:
// 1. Sąsiadem v, jest każdy wierzchołek u, dla którego r(u) jest jakimś wybrednym synem wierzchołka p ze ścieżki P(v),
// takim że krawędź do r(u) powstała przed krawędzią do każdego syna s wierzchołka p, który też jest na ścieżce P(v) (może być takich 1 albo 0).
//
// 2. Sąsiadem v, jest też każdy wierzchołek u, taki że ojciec p wierzchołka r(v) jest na ścieżce P(u),
// taki, że P(u) to pojedyńczy wierzchołek albo krawędź ścieżki P(u) bezpośrednio pod p powstała po wierzchołku r(v). 
//
// 3. Sąsiadem v będzie jeszcze oczywiście sam ojciec r(v) (o ile istnieje).
// 
// 4. Sąsiadami v są też jego wszyscy wybredni synowie.
// 
// Żeby dla wierzchołka sprawdzić jaki ma stopień możemy policzyć ile razy mu dodaliśmy z danego przypadku.
// Przypadki 3 i 4 są bardzo proste do utrzymywania w czasie stałym, skupmy się na pozostałych dwóch.
//
// Przypadek 1: Jak dodajemy zazdrosnego v, to dodajemy +1 do wag wszystkich ZAZDROSNYCH krawędzi P(v).
//              Żeby odczytać ile dodaliśmy do jakiegoś u, dla którego ojcem r(u) jest jakiś wierzchołek p,
//              sumujemy wagi wszystkich ZAZDROSNYCH krawędzi (syn, p) takich, że r(u) < syn.
//
// Przypadek 2: Jak dodajemy zazdrosnego v, to dodajemy +1 do wagi WYBREDNEJ krawędzi między r(v) a ojcem r(v).
//              Żeby odczytać ile dodaliśmy do jakiegoś u, idziemy po krawędziach (syn, ojciec) z p(u) od góry do dołu,
//              i sumujemy wagi wszystkich WYBREDNYCH krawędzi (syn', ojciec) takich, że syn > syn'.
//
// Na pierwszy rzut oka wygląda kwadratowo bo:
// 1) Krawędzi do synów też może byc liniowo wiele. 
// 2) Musimy przechodzić całą ścieżkę p(u) zarówno w dodawaniu jak i zapytaniu, jej długość może być liniowa.
//
// Poradźmy sobie najpierw z (1).
// Chcemy dla wierzchołka v poznać sumę wag wszystkich krawędzi pewnego typu do jego synów,
// którzy mają numery większe od jakiegoś syna x innego typu. 
// Możemy więc trzymać w każdym wierzchołku drzewo potęgowe na przedziale [1, liczba_synów] dla każdego typu krawędzi,
// które pozwoli nam dodawać 1 do pojedyńczej krawędzi, i sumować wartości na sufiksie.
// W ten sposób (1) da się zrobić logarytmicznie dla każdego syna.
//
// No ale nadal musimy w (2) liczyć (1) dla wszystkich wierzchołków na jakiejś ścieżce co brzmi bardzo czasochłonnie.
//
// Poradźmy sobie więc i z problemem (2). Skorzystamy w tym celu z HLD (Heavy/Light Decomposition).
// Możemy dzięki niemu podzielić każdą ścieżkę P(v) na logarytmicznie wiele podścieżek.
// Dodatkowo będziemy krzystać z tego, że każdy wierzchołek należy do dokładnie jednej ciężkiej ścieżki.
//
// Przypadek 1 - czyli ZAZDROSNY rozwiązujemy następująco 
// Żeby wykonać dodawanie do całej ścieżki dla każdego jej kawałka, który jest:
// Lekki - czyli jest jedną krawędzią - robimy to co wcześniej, +1 w drzewku odpowiadającego jej wierzchołka.
// Ciężki - Dla każdej ciężkiej ścieżki stawiamy wcześniej drzewo potęgowe, 
// które dla każdego prefiksu tej ścieżki będzie mówiło ile sumarycznie dodano do krawędzi z tego prefiksu.
// Teraz, żeby odczytać wynik wystarczy wziąć sumę wszystkich lekkich krawędzi z drzewa wierzchołka,
// i doliczyć wagę pojedyńczej krawędzi robiąc zapytanie na drzewie jej ciężkiej ścieżki.
// 
// Przypadek 2 - czyli WYBREDNY
// Dodawanie mamy tylko jedno, musimy zadbać o logarytmiczny odczyt.
// W tym celu znów dla każdej ciężkiej ścieżki postawimy sobie drzewo potęgowe.
// Tym razem będziemy w nim dodawać w punkcie i sumować na przedziale.
//
// Po pierwsze dla naszej krawędzi (ojciec, syn) dodamy tak jak wcześniej +1 do drzewa odpowiadającego jej ojcu.
// Dodatkowo dla ciężkiej krawędzi (ojciec, syn') ojca, dodamy +1 jeśli jest wybredna i syn < syn'.
//
// Teraz, żeby odczytać wynik gdy idziemy lekką krawędzią pytamy o sumę drzewo wierzchołka,
// a jak idziemy ciężką ścieżką, to pytamy drzewo ścieżki o sumę krawędzi które przechodzimy.
//
// Ale hola hola, robiąc tak możemy też dodać coś do nieistniejących jeszcze wierzchołków.
// Na szczęście wystarczy w momencie pierwszego pojawienia się wierzchołka v zapisać,
// że od deg(v) trzeba odjąć deg(v) jakie było na chwilę przed dodaniem v.
//
// Wychodzi nam z tego całkiem skomplikowane rozwiązanie w q * log^2(q), co jest niestety gorsze niż wzorcówka, 
// ale przy efektywnej implemetacji raczej wejdzie z racji na limit 10s.
// Hintem do szukania n * log(n) i zdiscardowania HLD w tym celu jest limit q <= 10*6.
