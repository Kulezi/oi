// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
using namespace std;
void fin(int &liczba) {
    char c = 0;
    liczba = 0;
    while (c < 33) c = getchar();
    do {
        liczba = (liczba << 1) + (liczba << 3) + c - '0';
        c = getchar();
    } while (c > 33);
}
int lazy[1 << 21];
int tree[1 << 21];
int n, q, a, b, w, xd, typ, x, k, m;
pair<int, int> res;
void update_tree(int node, int a, int b, int i, int j, int value) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];

        if (a != b) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    if (a > b || a > j || b < i) return;

    if (a >= i && b <= j) {
        tree[node] += value;

        if (a != b) {
            lazy[node * 2] += value;
            lazy[node * 2 + 1] += value;
        }

        return;
    }

    update_tree(node * 2, a, (a + b) / 2, i, j, value);
    update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, value);

    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query_tree(int node, int a, int b, int i, int j) {
    if (a > b || a > j || b < i) return INT_MIN;

    if (lazy[node] != 0) {
        tree[node] += lazy[node];

        if (a != b) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    if (a >= i && b <= j) return tree[node];

    int q1 = query_tree(node * 2, a, (a + b) / 2, i, j);
    int q2 = query_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j);

    int res = max(q1, q2);
    return res;
}

int main() {
    fin(n);
    fin(k);
    fin(m);
    for (int i = 1; i <= m; i++) {
        fin(a);
        fin(b);
        a--;
        b--;
        fin(w);
        // cout <<query_tree(1,0,n-1,a,b)<<endl;
        if (query_tree(1, 0, n - 1, a, b - 1) + w <= k)
            puts("T"), update_tree(1, 0, n - 1, a, b - 1, w);
        else
            puts("N");
    }
}