// Generatorka testów do zadania 'Turniej trójinformatyczny' z III etapu XXV OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int R(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int32_t main() {
	int n = 6;
	cout << n << endl;

	for (int c = 1; c <= 3; c++) {
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 1);
		shuffle(ord.begin(), ord.end(), rng);
		for (auto i : ord) cout << i << " ";
		cout << "\n";
	}

	int m = R(1, 5);
	cout << m << endl;
	while (m--) {
		int a = R(1, n-1);
		int b = R(a+1, n);
		if (R(0, 1)) swap(a, b);
		cout << a << " " << b << endl;
	}
}
