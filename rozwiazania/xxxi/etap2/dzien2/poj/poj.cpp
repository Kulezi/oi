// Rozwiązanie zadania 'Pojemniki' z II etapu XXXI OI. 
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n).
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int32_t main() {
	ios_base::sync_with_stdio(0);
	int n;
	ll k;
	cin >> n >> k;

	multiset<pair<ll, int>> s;
	for (int i = 1; i <= n; i++) {
		ll x;
		cin >> x;
		s.insert({x, i});
	}

	vector<vector<pair<int,ll>>> pojemniki;
	while (!s.empty()) {
		auto [min_ile, min_idx] = *s.begin();
		// Jeśli minimum jest większe niż k, to suma objętości jest większa niż n * k.
		if (min_ile > k) {
			cout << "NIE\n";
			return 0;
		}
		
		// Jeśli rozwiązanie istnieje, to istnieje też rozwiązanie, 
		// w którym składnik o najmniejszej objętości jest tylko w jednym pojemniku.
		// Dowód:
		// Załóżmy, że w jakimś rozwiązaniu są dwa pojemniki, w których jest ten składnik.
		// Zawsze możemy przenieść ten składnik z pojemnika, w którym jest go mniej do tego drugiego,
		// zamieniając go z resztą składnika drugiego. Zmieści się na pewno bo sumaryczna objętość
		// tego składnika nie przekracza k.
		pojemniki.push_back({{min_idx, min_ile}});
		ll zostalo = k - min_ile;
		if (zostalo > 0) {
			auto [max_ile, max_idx] = *(--s.end());
			if (max_idx != min_idx) {
				s.erase(--s.end());
				ll zabierane = min(max_ile, zostalo);
				if (zabierane < max_ile) {
					s.insert({max_ile - zostalo, max_idx});
				}
				pojemniki.back().push_back({max_idx, zabierane});
			}
		}

		// Nie można zrobić s.erase(s.begin()) bo maks mógł stać się nowym minem.
		s.erase(s.find({min_ile, min_idx}));
	}

	cout << "TAK\n";
	for (int i = 0; i < n; i++) {
		if (i >= pojemniki.size()) {
			cout << "0\n";
			continue;
		}
		cout << pojemniki[i].size() << " ";
		for (auto [idx, ile] : pojemniki[i]) cout << idx << " " << ile << " ";
		cout << "\n";
	}
}
