// Rozwiązanie do zadania 'Konkurs tańca towarzyskiego' z II etapu XXIX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(q * log(q))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

// Implementacja wzorcówki z https://oi.edu.pl/l/oi29_2_kon/.

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
#define cerr if(false)cerr
using namespace std;

constexpr int MAX_Q = 1'000'099;
int q;
pair<char, int> zapytania[MAX_Q];
struct Fenwick {
	// Każda krawędź może być dwa razy.
	int bit[MAX_Q * 2];
	void dodaj(int x, int delta) {
		for (; x < 2*MAX_Q; x |= x+1)
			bit[x] += delta;
	}

	int suma(int r) {
		int res = 0;
		for (; r >= 0; r = (r & (r+1)) - 1)
			res += bit[r];
		return res;
	}
};

int grupa[MAX_Q], x;
struct Drzewo {
	// Dół pierwszej krawędzi, tzn. odpowiedzi są na przedziały przeciwnej grupy niż jego.
	int pytana;
	vector<int> g[MAX_Q];
	int l[MAX_Q], r[MAX_Q], ojciec[MAX_Q];
	int T;

	int tin[MAX_Q], tout[MAX_Q];
	Fenwick fw;
	// Ustawiamy tylko kto jest czyim ojcem, potem wygenerujemy graf z listy ojców.
	void dodaj_krawedz(int nowy, int stary, char typ) {
		if (grupa[nowy] == pytana) {
			if (typ == 'Z') {
				// Będzie miał dokładnie tych samych sąsiadów at the moment.
				l[nowy] = l[stary];
				r[nowy] = r[stary];
			} else {
				// Będzie miał tylko swoją krawędź.
				l[nowy] = ojciec[stary];
				r[nowy] = stary;
			}
		} else {
			if (typ == 'Z') {
				// Wsadzamy nowego na środek najniższej krawędzi starego.
				ojciec[nowy] = ojciec[stary];
				ojciec[stary] = nowy;
			} else {
				// Nowy będzie miał tylko swoją krawędź.
				ojciec[nowy] = r[stary];
				
				// A temu staremu trzeba przedłużyć ścieżkę o tę nową krawędź.
				r[stary] = nowy;
			}
		}
	}

	void dfs(int u) {
		tin[u] = ++T;
		for (auto v : g[u])
			dfs(v);

		tout[u] = ++T;
	}

	void ponumeruj_krawedzie() {
		// Pułapka, wierzchołków jest max q + 2.
		for (int i = 1; i <= q + 2; i++) {
			g[ojciec[i]].push_back(i);
		}

		T = 0;
		dfs(0);
	}

	void wlacz_krawedz(int v) {

		cerr << __func__ << dbg(pytana) << dbg(v) << dbg(tin[v]) << dbg(tout[v]) << endl;
		// Może nie być takiej krawędzi.
		if (!tin[v]) return;
	
		fw.dodaj(tin[v], 1);
		fw.dodaj(tout[v], -1);
	}

	int znajdz_krawedz_do_potomka(int v, int potomek) {
		// Synowie są posortowani po czasach wejscia.
		// Wybinsearchujemy, która z krawędzi do nich jest przodkiem r[v].
		int lo = 0;
		int hi = g[v].size()-1;

		for (auto x : g[v]) {
			cerr << dbg(x) << dbg(tin[x]) << dbg(tout[x]) << endl;
		}

		cerr << dbg(tin[potomek]) << dbg(tout[potomek]) << endl;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			int m = g[v][mid];
			if (tin[m] > tout[potomek]) { 
				cerr << dbg(lo) << dbg(mid) << dbg(hi) << "B";
				hi = mid - 1;
			}
			else if (tout[m] < tin[potomek])
			{	
				cerr << dbg(lo) << dbg(mid) << dbg(hi) << "B";
				lo = mid + 1;
			} else {
				return m;
			}
		}

		return g[v][lo];
	}

	int zapytanie(int v) {
		// Jako, l[v] wskazuje na najwyższy wierzchołek ścieżki, trzeba jeszcze znaleźć faktyczny numer krawędzi.
		int gora = znajdz_krawedz_do_potomka(l[v], r[v]);
		cerr << __func__ << " " << dbg(v) << dbg(l[v]) << dbg(gora) << dbg(tin[gora]) << dbg(tin[r[v]]) << endl;
		return fw.suma(tin[r[v]]) - fw.suma(tin[gora]-1);
	}

} drzewo[3];

int przeciwna_grupa(int x) {
	if (x == 1) return 2;
	return 1;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> q;
	
	grupa[1] = drzewo[1].pytana = 1;
	drzewo[1].r[1] = 2;

	grupa[2] = drzewo[2].pytana = 2;
	drzewo[2].r[2] = 1;

	for (int i = 1, t = 2; i <= q; i++) {
		auto &[typ, v] = zapytania[i];
		cin >> typ >> v;
			
		if (typ == 'W' || typ == 'Z') {
			t++;
			grupa[t] = (typ == 'Z' ? grupa[v] : przeciwna_grupa(grupa[v]));
			for (int d = 1; d <= 2; d++)
				drzewo[d].dodaj_krawedz(t, v, typ);
		} else {
			assert(typ == '?');
		}
	}

	for (int i = 1; i <= 2; i++) {
		drzewo[i].ponumeruj_krawedzie();
	
		cerr << "drzewo " << dbg(i) << endl;
		for (int u = 0; u <= q; u++) {
			cerr << dbg(u) << dbg(drzewo[i].ojciec[u]) << endl;
			for (auto v : drzewo[i].g[u]) cerr << v << " ";
			cerr << endl;
		}

		for (int u = 1; u <= q; u++) {
			if (grupa[u] == drzewo[i].pytana) {
				cerr << dbg(u) << dbg(drzewo[i].l[u]) << dbg(drzewo[i].r[u]) << endl;
			}
		}
	}

	drzewo[1].wlacz_krawedz(2);
	drzewo[2].wlacz_krawedz(1);
	for (int i = 1, t = 2; i <= q; i++) {
		auto [typ, v] = zapytania[i];
			
		if (typ == 'W' || typ == 'Z') {
			t++;
			for (int d = 1; d <= 2; d++)
				drzewo[d].wlacz_krawedz(t);
		} else {
			cout << drzewo[grupa[v]].zapytanie(v) << "\n";
		}
	}


}

