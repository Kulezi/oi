// Rozwiązanie zadania 'Test na inteligencję' z I etapu XVII OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(s * log(m)), gdzie s to suma m_i z wejścia.
// Złożoność pamięciowa: O(m).

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1'000'005;
vector<int> occ[MAXN];

int32_t main() {
	ios_base::sync_with_stdio(0);
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int x;
		cin >> x;
		occ[x].push_back(i);
	}

	int n;
	cin >> n;
	while (n--) {
		int k;
		cin >> k;

		int i = 0;
		bool jest_podciagiem = true;
		while (k--) {
			int x;
			cin >> x;
			
			if (jest_podciagiem) {
				auto it = upper_bound(occ[x].begin(), occ[x].end(), i);
				if (it == occ[x].end()) {
					jest_podciagiem = false;
				} else {
					i = *it;
				}
			}
		}

		cout << (jest_podciagiem ? "TAK" : "NIE") << "\n";
	}
}
