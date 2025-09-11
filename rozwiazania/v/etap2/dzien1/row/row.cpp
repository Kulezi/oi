// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n).
// Punkty: 100 (upsolve).

#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = [" << x << "]\n"
using namespace std;

// Zwraca 2 do potegi n.
string pot2(int n) {
    string pot = "1";
    for (int i = 1; i <= n; i++) {
        int carry = 0;
        string nowa;
        for (int j = pot.size() - 1; j >= 0; j--) {
            int cyfra = (pot[j] - '0') * 2 + carry;
            carry = 0;

            if (cyfra >= 10) cyfra -= 10, carry++;
            nowa += (char)(cyfra + '0');
        }

        if (carry > 0) nowa += "1";
        reverse(nowa.begin(), nowa.end());
        pot = nowa;
    }

    return pot;
}

void solve(int tc) {
    int k;
    cin >> k;

    vector<int> len(k);
    for (int i = 0; i < k; i++) {
        cin >> len[i];
    }

    array<string, 2> s = {"", ""};
    array<int, 2> true_len = {0, 0};
    dbg(true_len[0]);
    dbg(true_len[1]);
    for (int eq = 0; eq < 2; eq++) {
        int l;
        cin >> l;

        cin >> s[eq];
        // cerr << s[eq] << endl;
        for (auto i : s[eq]) {
            if (i == '0' || i == '1')
                true_len[eq]++;
            else
                true_len[eq] += len[i - 'a'];
            dbg(i);
            dbg(eq);
            dbg(true_len[eq]);
            if (true_len[eq] > 10000) exit(1);
        }
    }

    cerr << true_len[0] << " " << true_len[1] << "\n";
    if (true_len[0] != true_len[1]) {
        // cerr << "A\n";
        cout << "0\n";
        return;
    }

    vector<vector<int>> numerek(k, vector<int>());
    int min_wolny_numer = true_len[0];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < len[i]; j++) {
            numerek[i].push_back(min_wolny_numer++);
        }
    }

    // Wierzcholki są trzech typów:
    // 1 - Pozycja w słowie wynikowym, jest ich true_len[0], numerki od 0 do true_len[0] - 1.
    // 2 - (Zmienna, pozycja w niej), jest ich też 2 * true_len[0], numerki od true_len[0] do
    // true_len + suma od 1 do k po |x_i|. 3 - Stała (0 albo 1)
    int VERTEX_0 = min_wolny_numer++;
    int VERTEX_1 = min_wolny_numer++;

    vector<vector<int>> g(min_wolny_numer, vector<int>());
    auto add_edge = [&](int a, int b) {
        // cerr << "add_edge " << a << " " << b << "\n";
        g[a].push_back(b);
        g[b].push_back(a);
    };

    // Krawędzie z pozycji w słowie wynikowym wychodzą albo do stałej która na nim stoi, albo do
    // pozycji w zmiennej:
    for (int eq = 0; eq < 2; eq++) {
        int pos = 0;
        for (auto x : s[eq]) {
            if (x == '0') {
                add_edge(VERTEX_0, pos);
                pos++;
            } else if (x == '1') {
                add_edge(VERTEX_1, pos);
                pos++;
            } else {
                for (int pos_x = 0; pos_x < len[x - 'a']; pos_x++) {
                    add_edge(pos, numerek[x - 'a'][pos_x]);
                    pos++;
                }
            }
        }
    }

    // Wynik to 2^(liczba spójnych w tym grafie osiagalnych z wierzchołków typu 1 (tych osiągalnych
    // z wierzchołków typu 3 nie wliczamy) bo za wszystko poza stałymi możemy podstawić albo 0 albo
    // 1).

    // DFS zajmie  O(|słowo wynikowe|) czasu.
    vector<int> vis(min_wolny_numer, 0);
    auto dfs = [&](int v, int c, auto &&self) -> void {
        vis[v] = c;
        for (auto u : g[v]) {
            if (!vis[u]) self(u, c, self);
        }
    };

    int spojne = 0;
    for (int i = 0; i < min_wolny_numer; i++) {
        if (!vis[i]) {
            spojne++;
            dfs(i, spojne, dfs);
        }
    }

    // Corner case, mamy sprzeczność w równaniach wynikającą ze stałych.
    if (vis[VERTEX_0] == vis[VERTEX_1]) {
        // cerr << "B\n";

        cout << "0\n";
        return;
    }

    if (vis[VERTEX_0]) spojne--;
    if (vis[VERTEX_1]) spojne--;

    cout << pot2(spojne) << "\n";
}

int32_t main() {
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
}