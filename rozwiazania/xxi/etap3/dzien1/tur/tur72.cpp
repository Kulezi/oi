// Rozwiązanie wolne do zadania 'Turystyka' z III etapu XXI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((1 + sqrt(2))^t * (n + m)) gdzie t = długość najdłuższej ścieżki
// Złożoność pamięciowa: O(n + m)
// Punkty: 72 (upsolve)
// Implementacja ze słabą stałą (swapowanie std::array jest wolne!)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 20005, INF = 10000000;
using DP = array<int, 9 * 9 * 9 * 9 * 9 + 5>;
vector<int> g[MAXN];
int vis[MAXN];

int c[MAXN], par[MAXN];
vector<int> P;

array<int, MAXN> P_idx;
// S - zbiór wierzchołków ze ścieżki, które są w dominating secie.
// D - zbiór wierzchołków ze ścieżki, które są zdominowane przez S.
void path_push(int v) {
    P_idx[v] = P.size();
    P.push_back(v);
}

void path_pop() {
    P_idx[P.back()] = -1;
    P.pop_back();
}

vector<int> sons[MAXN], ancestors[MAXN];

int dep[MAXN];
void split_edges(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) {
            dep[u] = dep[v] + 1;
            split_edges(u);
            sons[v].push_back(u);
        } else if (dep[u] < dep[v]) {
            ancestors[v].push_back(u);
        }
    }
}
DP dp_now, dp_future;

enum { UNDOMINATED, DOMINATED, TAKEN };

// Stablicowane constexpry żeby kompilator zoptymalizował dzielenie modulo, dodaje 16 pkt.
constexpr int pow3[11] = {1,
                          3,
                          3 * 3,
                          3 * 3 * 3,
                          3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3,
                          3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3};

int val(int mask, int pos) {
    mask /= pow3[pos];
    return mask % 3;
}

void change(int &mask, int pos, int new_val) { mask += (new_val - val(mask, pos)) * pow3[pos]; }

vector<int> good_masks[12];
// Mam zbiory A, S, B.
void dfs_dp(int v) {
    path_push(v);
    int h = P.size();
    dp_future.fill(INF);

    // Przerzucam v z B do S.
    for (int state : good_masks[h - 1]) {
        int state_take = state + TAKEN * pow3[P_idx[v]];
        int state_no_take = state;
        for (auto p : ancestors[v]) {
            if (P_idx[p] == -1) continue;
            if (val(state_take, P_idx[p]) != TAKEN) change(state_take, P_idx[p], DOMINATED);
            if (val(state_no_take, P_idx[p]) == TAKEN) change(state_no_take, P_idx[v], DOMINATED);
        }

        if (dp_future[state_take] > dp_now[state] + c[v])
            dp_future[state_take] = dp_now[state] + c[v];
        if (dp_future[state_no_take] > dp_now[state]) dp_future[state_no_take] = dp_now[state];
    }

    swap(dp_future, dp_now);
    for (auto u : sons[v]) {
        dfs_dp(u);
    }

    // Przerzucam v z S do A.
    for (int state : good_masks[h]) {
        if (state >= pow3[P_idx[v]]) {
            int mod_state = state % pow3[P_idx[v]];
            dp_now[mod_state] = min(dp_now[mod_state], dp_now[state]);
        }
        dp_now[state] = INF;
    }
    // Dorzucam obecny wierzcholek do dp
    path_pop();
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    P_idx.fill(-1);
    for (int h = 0; h <= 10; h++) {
        for (int i = 0; i < pow3[h]; i++) {
            bool good = true;
            for (int j = 0; j + 1 < h; j++) {
                if (val(i, j) == TAKEN && val(i, j + 1) == UNDOMINATED) good = false;
                if (val(i, j) == UNDOMINATED && val(i, j + 1) == TAKEN) good = false;
            }

            // if (h == 10 && val(i, 9) == UNDOMINATED) good = false;

            if (good) {
                good_masks[h].push_back(i);
            }
        }
    }

    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = 0;
    dp_now.fill(INF);
    dp_now[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            split_edges(i);
            dfs_dp(i);
        }
    }
    cout << dp_now[0] << "\n";
}