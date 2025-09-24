// Rozwiązanie do zadania 'Rozliczenia' z II etapu XXVI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * log(m))
// Złożoność pamięciowa: O(m), ze stałą 1.
// Punkty: 100 (upsolve)

struct Fenwick {
	int n;
	long long fw[1000005];

	void add(int x, long long delta) {
		for (;x < n; x |= x + 1)
			fw[x] += delta;
	}

	long long sum(int r) {
		long long res = 0;
		for (; r >= 0; r = (r & (r+1)) - 1)
			res += fw[r];
		return res;
	}

	long long sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
} fw;

struct Deque {
	int n, first, last;
	Deque() {}
	Deque(int n) : n(n), first(0), last(0) {}
	void push_back(long long x) {
		last = (last + 1) % n;
		if (last == first) {
			// Trzeba nadpisać to co było w miejscu pierwszego.
			x -= fw.sum(first, first);
			first = (first + 1) % n;
		}

		fw.add(last, x);
	}

	void set(int i, int k) {
		i = (last - i + 1 + n) % n;
		fw.add(i, k);
	}

	long long sum(int i) {
		int r = last;
		int l = (last - i + 1 + n) % n;
		if (l <= r) {
			return fw.sum(l, r);
		} else {
			return fw.sum(0, r) + fw.sum(l, n-1);
		}
	}
};

Deque dq;
void inicjuj(int m) {
	dq = Deque(m);
	fw.n = m;
	for (int i = 0; i < m; i++) fw.fw[i] = 0;
}

void dodaj(int k) {
	dq.push_back(k);
}

void koryguj(int i, int k) {
	dq.set(i, k);
}

long long suma(int i) {
	return dq.sum(i);
}

