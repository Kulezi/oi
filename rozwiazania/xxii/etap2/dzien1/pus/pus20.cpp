// Rozwiązanie wolne do zadania 'Pustynia' z II etapu XXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(m * n^2)
// Złożoność pamięciowa: O(m * n^2)
// Punkty: 20 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 100005;
int glebokosc[MAXN], oryginal[MAXN], out[MAXN];
vector<int> grev[MAXN];
int n, s, m;
void add_edge(int src, int dst) {
    out[src]++;
    grev[dst].push_back(src);
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    cin >> n >> s >> m;
    for (int i = 1; i <= n; i++) {
        glebokosc[i] = 1;
    }

    while (s--) {
        int p, d;
        cin >> p >> d;
        glebokosc[p] = d;
        oryginal[p] = d;
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        vector<bool> czy_dol(r - l + 1, false);
        while (k--) {
            int x;
            cin >> x;
            czy_dol[x-l] = true;
        }

        for (int i = l; i <= r; i++) {
            for (int j = l; j <= r; j++) {
                if (czy_dol[i-l] && !czy_dol[j-l]) {
                    add_edge(i, j);
                }
            }
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!out[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : grev[u]) {
            glebokosc[v] = max(glebokosc[v], glebokosc[u] + 1);
            out[v]--;
            if (!out[v]) q.push(v);
        }
    }


    for (int u = 1; u <= n; u++) {
        if (out[u] || glebokosc[u] > 1'000'000'000 || (oryginal[u] && glebokosc[u] != oryginal[u])) {
            cout << "NIE\n";
            return 0;
        }
        for (auto v : grev[u]) {
            if (glebokosc[u] >= glebokosc[v]) {
                cout << "NIE\n";
                return 0;
            }
        }
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; i++) {
        cout << glebokosc[i] << " ";
    }

    cout << "\n";
}