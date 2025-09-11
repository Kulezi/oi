// Rozwiązanie zadania 'Konduktor' z II etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n)).
// Złożoność pamięciowa: O(n).
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define cerr if(false)cerr
#define dbg(x) #x << " = " << printv(x) << " "
using namespace std;
constexpr int MOD = 1'000'000'007;

string printv(int v) {
	return to_string(v);
}

string printv(vector<int> v) {
	stringstream ss;
	ss << "[ ";
	for (auto i : v) ss << i << " ";
	ss << "]";
	return ss.str();
}

string printv(deque<pair<int,int>> v) {
	stringstream ss;
	ss << "[ ";
	for (auto [a, b] : v) ss << "(" << a << ", " << b << ") ";
	ss << "]";
	return ss.str();
}

string printv(vector<pair<int,int>> v) {
	stringstream ss;
	ss << "[ ";
	for (auto [a, b] : v) ss << "(" << a << ", " << b << ") ";
	ss << "]";
	return ss.str();
}

void solve() {
	int m, n;
	cin >> m >> n;

	vector<pair<int,int>> przedzialy(n);
	for (auto &[l, r] : przedzialy) cin >> l >> r;

	// Dla uproszczenia dodaję przedziały [0, 1] i [m, m+1], odejmę sobie potem co trzeba od wyniku.
	przedzialy.emplace_back(0, 1);
	przedzialy.emplace_back(m, m+1);

	sort(przedzialy.begin(), przedzialy.end());
	
	// Usuwam przedziały zawierające w pełni jakiś inny przedział.
	deque<pair<int, int>> otwarte, dobre;
	for (auto [l, r] : przedzialy) {
		while (!otwarte.empty() && otwarte.front().second <= l) {
			dobre.emplace_back(otwarte.front());
			otwarte.pop_front();
		}
		while (!otwarte.empty() && otwarte.back().second >= r)
			otwarte.pop_back();
		
		otwarte.emplace_back(l, r);
	}

	
	dobre.emplace_back(m, m+1);

	cerr << dbg(przedzialy) << endl;
	cerr << dbg(otwarte) << endl;
	cerr << dbg(dobre) << endl;

	vector<int> wszystkie_konce;
	for (auto [l, r] : przedzialy) {
		wszystkie_konce.push_back(l);
		wszystkie_konce.push_back(r);
	}
	sort(wszystkie_konce.begin(), wszystkie_konce.end());
	
	vector<int> (2*n+2, 0);

	// Indeks ostatniego dobrego przedziału, który musiał już zostać wbity.
	int j_przedzial = 0;
	int lewy = 0;

	vector<int> sposoby(wszystkie_konce.size(), 0), gwozdzi(wszystkie_konce.size());
	vector<int> suma(dobre.size() + 5, 0);
	
	suma[0] = sposoby[0] = 1;

	for (int i = 1; i + 1 < wszystkie_konce.size(); i++) {
		int l = wszystkie_konce[i], r = wszystkie_konce[i+1];
		while (j_przedzial + 1 < dobre.size() && dobre[j_przedzial + 1].second <= l) {
			j_przedzial++;
		}
		
		while (wszystkie_konce[lewy+1] <= dobre[j_przedzial].first) {
			int g = gwozdzi[lewy];
			suma[g] = (suma[g] - sposoby[lewy]) % MOD;
			if (suma[g] < 0) suma[g] += MOD;
			
			lewy++;
		}

		int g = gwozdzi[lewy] + 1;
		gwozdzi[i] = g;
		sposoby[i] = 1LL * suma[g-1] * (r - l) % MOD;
		cerr << dbg(i) << dbg(lewy) << dbg(gwozdzi[i]) << dbg(sposoby[i]) << endl;
		suma[g] = (suma[g] + sposoby[i]) % MOD;
	}

	cerr << dbg(wszystkie_konce) << endl
		 << dbg(sposoby) << endl 
		 << dbg(gwozdzi) << endl
		 << dbg(suma) << endl;

	int g = gwozdzi[lewy];
	cout << g << " " << suma[g] << "\n";
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	int z;
	cin >> z;

	while (z--) solve();
}
