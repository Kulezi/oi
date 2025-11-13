// Rozwiązanie alternatywne zadania 'Ciąg binarny' z II etapu XXXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n + q) * log^2(n)).
// Złożoność pamięciowa: O(n)
// Punkty: 73 (upsolve) - rozwiązanie na parallel binsearch.

#include <bits/stdc++.h>
#define cerr if(false)cerr
#define dbg(x) " " << #x << " = " << x << "\n"
using namespace std;
constexpr int MAXN = 1'000'005, MAX_S = 1'000'000'000;
int n, q;

int d[MAXN], pref[MAXN];

struct Zapytanie {
	int l, r, k;
	int l_blok, r_blok;
	int wynik = 0;
} zapytanie[MAXN];

struct Blok {
	int l, r, len;
} blok[MAXN];

// Zwraca parę (długość, koszt).
pair<int, int> utnij(Blok &blok, Zapytanie &zap) {
	int l = max(zap.l, blok.l);
	int r = min(zap.r, blok.r);
	return {r - l + 1, 2 - (l == zap.l) - (r == zap.r)};
}

int K = 0;

// Zapytanie o sumę pierwszych k maksimów (w skrócie kajmak).
struct Kajmak {
	int i; // Numer zapytania na wejściu, do aktualizacji wyniku.
	int k; // Ile największych wartości szukamy.
	int bonus; // Ile wliczyliśmy do wyniku ze skrajnych.

	int lo = 0, hi = MAX_S, mid = MAX_S / 2;
	Kajmak() {}
	Kajmak(int i, int k, int bonus) : i(i), k(k), bonus(bonus) {}
} kajmak[4 * MAXN];

// Zwraca pierwszy blok z końcem >= x.
int znajdz_blok(int x) {
	int lo = 0, hi = (n + 1) / 2;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (blok[mid].r < x) lo = mid + 1;
		else hi = mid;
	}
	
	cerr << __func__ << dbg(x) << dbg(lo) << endl;
	return lo;
}

struct Fenwick {
	int fw[MAXN];
	void clear() { for (int i = 0; i < MAXN; i++) fw[i] = 0; }
	void add(int x, int delta) {
		for (; x < MAXN; x |= x + 1) fw[x] += delta;
	}
	int sum(int r) {
		int res = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) res += fw[r];
		return res;
	}

	int sum(int l, int r) { return sum(r) - sum(l - 1); }
} fw_sum, fw_cnt;

vector<int> kajmak_ord, blok_ord;
void parallel_binsearch() {
	cerr << __func__ << endl;
	sort(kajmak_ord.begin(), kajmak_ord.end(), [&](int a, int b) { return kajmak[a].mid > kajmak[b].mid; });
	int j = 0;
	for (auto i : kajmak_ord) {
		auto &kaj = kajmak[i];
		while (j < blok_ord.size() && blok[blok_ord[j]].len >= kaj.mid) {
			int x = blok_ord[j];
			fw_cnt.add(x, 1);
			j++;
		}
		
		int l = zapytanie[kaj.i].l_blok + 1;
		int r = zapytanie[kaj.i].r_blok - 1;
		int ile = fw_cnt.sum(l, r);

		if (kaj.lo < kaj.hi) {
			if (ile >= kaj.k) kaj.lo = kaj.mid;
			else kaj.hi = kaj.mid - 1;
			kaj.mid = (kaj.lo + kaj.hi + 1) / 2;
		}
	}

	fw_cnt.clear();
}



void maksuj_kajmakami() {
	sort(kajmak_ord.begin(), kajmak_ord.end(), [&](int a, int b) { return kajmak[a].mid > kajmak[b].mid; });
	cerr << __func__ << endl;
	int j = 0;
	for (auto i : kajmak_ord) {
		auto &kaj = kajmak[i];
		while (j < blok_ord.size() && blok[blok_ord[j]].len >= kaj.mid) {
			int x = blok_ord[j];
			fw_sum.add(x, blok[x].len);
			cerr << "add " << x << " " << blok[x].len << endl;
			fw_cnt.add(x, 1);
			j++;
		}
		
		int l = zapytanie[kaj.i].l_blok + 1;
		int r = zapytanie[kaj.i].r_blok - 1;
		int ile = fw_cnt.sum(l, r);
		int sum = fw_sum.sum(l, r);
		
		cerr << dbg(ile) << dbg(kaj.k);
		cerr << dbg(sum) << dbg(ile - kaj.k) << "*" << dbg(kaj.mid) << dbg(kaj.bonus) << endl;
		zapytanie[kaj.i].wynik = max(zapytanie[kaj.i].wynik, sum - (ile - kaj.k) * kaj.mid + kaj.bonus);
	}
}



int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		pref[i] = pref[i - 1] + d[i];
	}

 	for (int i = 0; 2*i + 1 <= n; i++) {
		blok[i].l = pref[2*i+1] - d[2*i+1] + 1;
		blok[i].r = pref[2*i+1];
		blok[i].len = blok[i].r - blok[i].l + 1;
		blok_ord.push_back(i);
	}

	sort(blok_ord.begin(), blok_ord.end(), [&](int a, int b) { return blok[a].len > blok[b].len; });

	for (int i = 1; i <= q; i++) {
		auto &z = zapytanie[i];
		cin >> z.l >> z.r >> z.k;
	
		// Znajdujemy pierwszy i ostatni blok jedynek z którym mamy przecięcie.
		z.l_blok = znajdz_blok(z.l);
		z.r_blok = znajdz_blok(z.r);
		if (blok[z.r_blok].l > z.r) z.r_blok--;

		cerr << dbg(i) << dbg(z.l_blok) << dbg(z.r_blok) << endl;
		
		// Zależnie od tego czy stykają się z końcem przedziału z zapytania kosztują 0/1/2 zmian.
		auto [dlugosc_l, koszt_l] = utnij(blok[z.l_blok], z);
		auto [dlugosc_r, koszt_r] = utnij(blok[z.r_blok], z);
		cerr << dbg(dlugosc_l) << dbg(koszt_l) << dbg(dlugosc_r) << dbg(koszt_r);
	
		// Najpierw sprzątamy trywialne zapytania.
		if (z.l_blok > z.r_blok || dlugosc_l <= 0) {
			// Nie ma żadnej jedynki w przedziale.
			z.wynik = 0;
		} else if (z.l_blok == z.r_blok) {
			// Jest tylko jeden przedział jedynek z którym się przecinamy.
			z.wynik = (koszt_l <= z.k ? dlugosc_l : 0);
		} else if (z.l_blok + 1 == z.r_blok) {
			// Są dokładnie dwa przedziały z jedynkami (mogą być ucięte).
			z.wynik = max({
				(dlugosc_l + dlugosc_r) * (koszt_l + koszt_r <= z.k), // Wzięte oba.
				dlugosc_l * (koszt_l <= z.k), // Tylko lewy.
				dlugosc_r * (koszt_r <= z.k), // Tylko prawy.
			});
		} else {
			// Cztery przypadki, względem tego czy bierzemy skrajne czy nie.
			// Zależnie od tego trzeba różnie postępować.	
			auto nowe = [&](int k, int bonus) {
				if (k < 0) return;
				cerr << dbg(k) << dbg(bonus) << "->" ;
				int l = z.l_blok + 1;
				int r = z.r_blok - 1;
				k = min(k / 2, r - l + 1);
				cerr << dbg(k) << dbg(bonus) << endl;
				if (k < 0) return;
				if (k == 0) {
					z.wynik = max(z.wynik, bonus);
					return;
				}

				kajmak_ord.push_back(K);
				kajmak[K++] = Kajmak(i, k, bonus);
			};

			// 1: Nie biorąc żadnego z dwóch.
			nowe(z.k, 0);
			// 2: Biorąc tylko lewy.
			nowe(z.k - koszt_l, dlugosc_l);
			// 3: Biorąc tylko prawy.
			nowe(z.k - koszt_r, dlugosc_r);
			// 4: Biorąc oba.
			nowe(z.k - koszt_l - koszt_r, dlugosc_l + dlugosc_r); 
		}
	}

	// Teraz wystarczy odpowiedzieć na wszystkie kajmaki.
	for (int i = 0; i <= 30; i++) parallel_binsearch();
	maksuj_kajmakami();

	for (int i = 1; i <= q; i++) {
		cout << zapytanie[i].wynik << "\n";
	}
}

