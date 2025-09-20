// Rozwiązanie zadania 'Przelewy' z II etapu XXV OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n * log(n)).
// Złożoność pamięciowa: O(n).
// Punkty: 100 (upsolve).

#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;
constexpr int MAXN = 1'000'005, BASE = 1'000'000'000;
ll brak[MAXN], up[MAXN], down[MAXN], par[MAXN];
int deg[MAXN];
vector<int> g[MAXN];

// Wynik może wyjść nawet 10^24.
// Na konkursie nie było pythona ani __int128_t.
struct BigInt {
	vector<int> d;
	BigInt(ll x) {
		if (x >= BASE) d = {x / BASE, x % BASE};
		else d = {x};
	}

	BigInt(vector<int> &x) : d(x) {}
	BigInt operator+(const BigInt &y) {
		vector<int> nowy;
		int nadmiar = 0;

		int i = d.size() - 1;
		int j = y.d.size() - 1;
		while (i >= 0 || j >= 0) {
			int a = (i >= 0 ? d[i] : 0);
			int b = (j >= 0 ? y.d[j] : 0);
			int sum = a + b + nadmiar;
			if (sum >= BASE) nadmiar = 1, sum -= BASE;
			else nadmiar = 0;
			nowy.push_back(sum);
			i--;
			j--;
		}
		if (nadmiar) nowy.push_back(1);
	
		reverse(nowy.begin(), nowy.end());
		return BigInt(nowy);
	}

	// Mnożenie w log_2(x), bo jestem leniwy.
	BigInt operator*(ll x) {
		if (d.size() == 1 && d[0] == 0) return BigInt(0LL);
		BigInt pot = BigInt(d);
		BigInt res(0LL);
		while (x > 0) {
			if (x & 1) res = res + pot;
			pot = pot + pot;
			x /= 2;
		}

		return res;
	}

	friend ostream& operator<<(ostream &out, const BigInt &x) {
		out << x.d[0];
		for (int i = 1; i < x.d.size(); i++) {
			out << setfill('0') << setw(9) << x.d[i];
		}
		return out;
	}
} wynik(0LL);

int32_t main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> brak[i];
	}

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		brak[i] = x - brak[i];
	}

	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		deg[a]++;
		deg[b]++;
		par[a] += b;
		par[b] += a;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 1) q.push(i);
	}

	// Nie liczę dfsem, bo mi pamięci nie starczało, trik na obgryzanie liści.
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		up[v]++;
		
		int p = par[v];

		// Spełniam żądania synów.
		brak[v] += 1LL * down[v] * sz(g[v]);
		wynik = wynik + BigInt(down[v]);
		// Niektórym mogłem oddać za dużo, to mi oddają.
		for (auto s : g[v]) {
			brak[s] -= down[v];
			if (s != p) {
				wynik = wynik + BigInt(-brak[s]) * up[s];
				brak[v] += brak[s];
			}
		}
	
		// W korzeniu nie mam już opcji zabrać/oddać ojcu.
		if (deg[v] == 0 && brak[v] != 0) {
			cout << "NIE\n";
			exit(0);
		}
	
		if (brak[v] < 0) {
			ll nadmiar = -brak[v];
			// Wysyłam nadmiar do ojca.
			wynik = wynik + BigInt(nadmiar) * up[v];
			brak[p] -= nadmiar;
			brak[v] = 0;
		} else {
			// Żądam od ojca, żeby wysłał mi tyle ile potrzebuję.
			down[p] = max(down[p], brak[v]);
		}

		deg[v]--;
		par[p] -= v;
		deg[p]--;
		up[p] += up[v];
		if (deg[p] == 1) {
			q.push(p);
		}
	
	}


	cout << "TAK\n";
	cout << wynik << "\n";
}

