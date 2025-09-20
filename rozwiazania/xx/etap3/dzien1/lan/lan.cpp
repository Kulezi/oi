// Rozwiązanie zadania 'Łańcuch kolorowy' z III etapu XX OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n + m)
// Złożoność pamięciowa: O(n + m).
// Punkty: 100 (upsolve)

#include <iostream>
#define cerr if(false)cerr
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1'000'005;
int l[MAXN], c[MAXN], a[MAXN], brakuje[MAXN];

int zle;
void dodaj(int kolor, int delta) {
	if (brakuje[kolor] == 0) zle++;
	brakuje[kolor] += delta;
	if (brakuje[kolor] == 0) zle--;
	cerr << dbg(kolor) << " " << dbg(delta) << "-> " << dbg(brakuje[kolor]) << " " << dbg(zle) <<  endl;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;

	long long sum = 0;
	for (int i = 1; i <= m; i++) {
		cin >> l[i];
		sum += l[i];
	}


	for (int i = 1; i <= m; i++) {
		cin >> c[i];
		
		dodaj(c[i], l[i]);
	}

	int wynik = 0;
	for (int i = 1; i <= n; i++) {
		cerr << dbg(i) << endl;
		cin >> a[i];
		dodaj(a[i], -1);
		if (i > sum)
			dodaj(a[i-sum], 1);
		if (i >= sum)
			if (zle == 0) wynik++;
	}

	cout << wynik << "\n";

}
