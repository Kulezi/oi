// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n^4)
// Punkty: 70 (upsolve)

#include <bits/stdc++.h>
#define MAX_POINTS 305
#define ll long long
#define dbg(x) cerr << #x << " = " << x << "\n"
using namespace std;
int n, o, ob;
int x[MAX_POINTS], y[MAX_POINTS], v[MAX_POINTS];
ll under[MAX_POINTS][MAX_POINTS];
ll dp[MAX_POINTS][MAX_POINTS], ans = -2e18;
ll det(int a, int b, int c) {
	return 1LL * (x[b] - x[a]) * (y[c] - y[a]) - 1LL * (x[c] - x[a]) * (y[b] - y[a]);
}

vector<int> ord;
void preprocess() {
	for (int i1 = 0; i1 < n; ++i1) {
		for (int j1 = i1; j1 < n; ++j1) {
			int i = ord[i1];
			int j = ord[j1];
			if (x[i] > x[j]) swap(i, j);

			for (int k = 1; k <= n; k++) {
				if (k == i || k == j) continue;
				if (i == j && x[k] == x[i] && y[k] < y[i]) {
					under[i][j] += v[k]; 
				} else if (x[k] >= min(x[i], x[j]) && x[k] <= max(x[i], x[j]) && det(i, j, k) < 0) {
					under[i][j] += v[k];
				}
			}

			under[j][i] = under[i][j];
		}
	}
}

bool lex_comp(int a, int b) {
	if(y[a] == y[b]) {
		return x[a] < x[b];
	}

	return y[a] > y[b];
}

bool angle_comp(int a, int b) {
	return 1LL * (x[a] - x[o]) * (y[b] - y[o]) < 1LL * (x[b] - x[o]) * (y[a] - y[o]);
}

bool angle_comp_b(int a, int b) {
	if (1LL * (y[a] - y[ob]) * (y[b] - y[ob]) > 0) {
		return 1LL * (x[a] - x[ob]) * (y[b] - y[ob]) < 1LL * (x[b] - x[ob]) * (y[a] - y[ob]);
	} else if (y[a] != y[ob] && y[b] != y[ob]) {
		return y[a] < y[ob];
	} else if (y[a] == y[ob] && x[a] > x[ob]) {
		return 1;
	} else if (y[b] == y[ob] && x[b] > x[ob]) {
		return 0;
	} else {
		return y[a] < y[b];
	}
}

ll tru(int o, int b, int a) {
	ll res = 0;
	for (int i = 1; i <= n; i++) {
		if (i == o || i == b || i == a) continue;
		if (det(o, b, i) < 0 && det(b, a, i) < 0 && det(a, o, i) < 0) res += v[i];
	}

	return res;
}

ll inside(int o, int b, int a) {
	ll res = 0;
	if (x[o] < x[b]) {
		if (x[b] < x[a]) {
			return under[o][b] + under[b][a] - under[a][o] - under[b][b];
		} else if (x[o] <= x[a]) {
			return under[o][b] - under[b][a] - under[a][o] + under[a][a] - v[a];
		} else {
			return under[o][b] - under[b][a] + under[a][o] - under[o][o];
		}
	} else {
		if (x[a] <= x[b]) {
			return under[a][o] - under[o][b] - under[a][b] + under[b][b] - v[b];
		} else {
			return under[a][o] - under[o][b] + under[b][a] - under[a][a];
		}
	}

}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i] >> y[i] >> v[i];
	}

	for (int i = 1; i <= n; ++i)
		ord.push_back(i);

	sort(ord.begin(), ord.end(), lex_comp);

	preprocess();

	for (int i = 1; i < n; ++i) {
		o = ord[i - 1];
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				dp[j][k] = -2e18;
			}
		}

		vector<int> sorted(ord.begin() + i, ord.end());
		sort(sorted.begin(), sorted.end(), angle_comp);

		for (int j = 0; j + 1 < sorted.size(); ++j) {
			int b = sorted[j];
			ob = b;
			deque<int> ord_prev = {o}, ord_next = {o};
			for (int k = 0; k < j; ++k) {
				ord_prev.push_back(sorted[k]);
			}

			for (int k = j + 1; k < sorted.size(); ++k) {
				ord_next.push_back(sorted[k]);
			}

			sort(ord_prev.begin(), ord_prev.end(), angle_comp_b);
			sort(ord_next.begin(), ord_next.end(), angle_comp_b);
			while (ord_prev.front() != o) {
				ord_prev.push_back(ord_prev.front());
				ord_prev.pop_front();
			}

			while (ord_next.front() != o) {
				ord_next.push_back(ord_next.front());
				ord_next.pop_front();
			}

//			cerr << o << " -- " << ob << " " << "\n";
//			cerr << "prev: ";
//			for (auto k : ord_prev) cerr << k << " ";
//			cerr << "\nnext: ";
//			for (auto k : ord_next) cerr << k << " ";
//			cerr << "\n";

			ll acc = -2e18;
			int l = 0;
			ord_next.pop_front();
			for (auto k : ord_next) {
				while (l + 1 < ord_prev.size() && det(ord_prev[l + 1], b, k) < 0) {
					acc = max(acc, dp[ord_prev[++l]][b]);
				}

				//dbg(o); dbg(b); dbg(k); dbg(ord_prev[l]);


				dp[b][k] = max(acc + inside(o, b, k) + v[k], inside(o, b, k) + v[b] + v[k]);
				ans = max(ans, dp[b][k] + v[o]);
				//cerr << o << " " << b << " " << k << " " << dp[b][k] + v[o] << "\n";
			}
		}
	}

	cout << ans;
}