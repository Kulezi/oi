// Rozwiązanie zadania 'Ciąg binarny' z II etapu XXXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n + q) * log(n))
// Złożoność pamięciowa: O(n * log(n))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) " " << #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005, MAX_S = 1'000'000'000;
int n, q;

int d[MAXN], pref[MAXN];

struct Blok {
	int l, r, len;
} blok[MAXN];

// Zwraca parę (długość, koszt).
pair<int, int> utnij(Blok &blok, int zl, int zr) {
	int l = max(zl, blok.l);
	int r = min(zr, blok.r);
	return {r - l + 1, 2 - (l == zl) - (r == zr)};
}


// Zwraca pierwszy blok z końcem >= x.
int znajdz_blok(int x) {
	int lo = 0, hi = (n + 1) / 2;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (blok[mid].r < x) lo = mid + 1;
		else hi = mid;
	}
	
	return lo;
}

// Zbita reprezentacja mapowań w jeden wektor bo overhead bardzo bolał.
vector<int> c;
vector<long long> preff = {0};
int NODES = 1;
struct WaveNode {
    int lChild = 0, rChild = 0, offset, poffset;

    int mapLeft(int i) {
        if (i < 0) return -1;
        return i - c[offset+i];
    }

    int mapRight(int i) {
        if (i < 0) return -1;
        return c[offset+i] - 1;
    }

    int sum(int l, int r) {
        return preff[poffset+r] - preff[poffset+l-1];
    }
} wave[MAXN * 30];

int sk[MAXN];
vector<int> dlugosci, sorted, ord;
void wave_build(vector<int> &v, int pos = 1, int lo = 0, int hi = ord.size()) {
    wave[pos].poffset = preff.size();
    for (auto i : v) {
        preff.push_back(preff.back() + dlugosci[i]);
    }
    if (lo == hi || v.empty()) {
        return;
    }

    int m = (lo + hi) / 2;
    vector<int> l, r;
    wave[pos].offset = c.size();
    for (auto i : v) {
        if (sk[i] <= m) l.push_back(i);
        else r.push_back(i);
        c.push_back(r.size());
    }

    wave[pos].lChild = ++NODES;
    wave_build(l, wave[pos].lChild, lo, m);
    wave[pos].rChild = ++NODES;
    wave_build(r, wave[pos].rChild, m+1, hi);
}

// Szuka największych elementów w przedziale.
// Zwraca (liczba_elementów, suma_elementów) 
pair<int,int> wave_query(int pos, int l, int r, int k, int lo = 0, int hi = ord.size()) {
    // cerr << __func__ << dbg(pos) << dbg(l) << dbg(r) << dbg(k) << dbg(lo) << dbg(hi) << "=> " << dbg(wave[pos].sum(l, r)) << endl;
    if (!pos || l > r) return {0, 0};
    if (r - l + 1 <= k) {
        return {r - l + 1, wave[pos].sum(l, r)};
    }
    // Zachodzi r - l + 1 > k
    if (lo == hi) {
        return {k, k * wave[pos].sum(l, l)};
    }

    int m = (lo + hi) / 2;
    auto [cnt, sum] = wave_query(wave[pos].rChild, wave[pos].mapRight(l-1)+1, wave[pos].mapRight(r), k, m+1, hi);
    k -= cnt;
    if (k > 0) {
        auto [l_cnt, l_sum] = wave_query(wave[pos].lChild, wave[pos].mapLeft(l-1)+1, wave[pos].mapLeft(r), k, lo, m);
        cnt += l_cnt;
        sum += l_sum;
    }

    return {cnt, sum};
}


int32_t main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		pref[i] = pref[i - 1] + d[i];
	}

    // Interesują mnie tylko jedynki.
 	for (int i = 0; 2*i + 1 <= n; i++) {
		blok[i].l = pref[2*i+1] - d[2*i+1] + 1;
		blok[i].r = pref[2*i+1];
		blok[i].len = blok[i].r - blok[i].l + 1;
        dlugosci.push_back(blok[i].len);
        ord.push_back(ord.size());
	}

    // Skalujemy współrzędne, żeby było q * log(n) zamiast q * log(S).
    sorted = ord;
    sort(sorted.begin(), sorted.end(), [&](const auto &lhs, const auto &rhs) {
        return dlugosci[lhs] < dlugosci[rhs];
    });

    for (int i = 0; i < (int)sorted.size(); i++) sk[sorted[i]] = i;
    
    wave_build(ord);
	for (int i = 1; i <= q; i++) {
        int l, r, k; 
		cin >> l >> r >> k;
	
        int wynik = 0;

		// Znajdujemy pierwszy i ostatni blok jedynek z którym mamy przecięcie.
		int l_blok = znajdz_blok(l);
		int r_blok = znajdz_blok(r);
		if (blok[r_blok].l > r) r_blok--;
		
		// Zależnie od tego czy stykają się z końcem przedziału z zapytania kosztują 0/1/2 zmian.
		auto [dlugosc_l, koszt_l] = utnij(blok[l_blok], l, r);
		auto [dlugosc_r, koszt_r] = utnij(blok[r_blok], l, r);
	
		// Najpierw sprzątamy trywialne zapytania.
		if (l_blok > r_blok || dlugosc_l <= 0) {
			// Nie ma żadnej jedynki w przedziale.
			wynik = 0;
		} else if (l_blok == r_blok) {
			// Jest tylko jeden przedział jedynek z którym się przecinamy.
			wynik = (koszt_l <= k ? dlugosc_l : 0);
		} else if (l_blok + 1 == r_blok) {
			// Są dokładnie dwa przedziały z jedynkami (mogą być ucięte).
			wynik = max({
				(dlugosc_l + dlugosc_r) * (koszt_l + koszt_r <= k), // Wzięte oba.
				dlugosc_l * (koszt_l <= k), // Tylko lewy.
				dlugosc_r * (koszt_r <= k), // Tylko prawy.
			});
		} else {
			// Cztery przypadki, względem tego czy bierzemy skrajne czy nie.
			// Zależnie od tego trzeba różnie postępować.	
			auto maksuj = [&](int qk, int bonus) {
				if (qk < 0) return;
				int ql = l_blok + 1;
				int qr = r_blok - 1;
				qk = min(qk / 2, qr - ql + 1);
				if (qk < 0) return;
				if (qk == 0) {
					wynik = max(wynik, bonus);
					return;
				}
                
                auto [_, sum] = wave_query(1, ql, qr, qk);
                // cerr << "wave_query " << dbg(ql) << dbg(qr) << dbg(qk) << "=> "  << dbg(sum) << dbg(bonus) << endl;
                wynik = max(wynik, sum + bonus);
            };

			// 1: Nie biorąc żadnego z dwóch.
			maksuj(k, 0);
			// 2: Biorąc tylko lewy.
			maksuj(k - koszt_l, dlugosc_l);
			// 3: Biorąc tylko prawy.
			maksuj(k - koszt_r, dlugosc_r);
			// 4: Biorąc oba.
			maksuj(k - koszt_l - koszt_r, dlugosc_l + dlugosc_r); 
		}

        cout << wynik << "\n";
	}
}

