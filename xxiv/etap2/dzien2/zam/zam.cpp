// Rozwiązanie do zadania 'Zamek' z II etapu XXIV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O((n + m) * log(n))
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int BAN = 0, MAXN = 1'000'005;
int w, h, n, m;
bool ban[MAXN];
int dis[MAXN];
vector<int> g[MAXN];

struct Event {
    int min_x, max_x;
    int min_y, max_y;
    int id;
};

void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

void make_edges(vector<Event> &events) {
    sort(events.begin(), events.end(), [&](auto &lhs, auto &rhs) {
        if (lhs.min_x == rhs.min_x) return lhs.min_y < rhs.min_y;
        return lhs.min_x < rhs.min_x;
    });

    set<pair<int, int>> s;
    for (auto &e : events) {
        auto it = s.lower_bound({e.min_y, 0});
        if (e.id == BAN) {
            assert(it != s.begin());
            it = prev(it);
            ban[it->second] = true;
        } else {
            int tallest = 0;
            if (it->first > e.min_x && it != s.begin()) tallest = prev(it)->second;

            while (it != s.end() && it->first < e.max_y) {
                tallest = it->second;
                auto nxt = next(it);
                s.erase(it);
                add_edge(e.id, it->second);
                it = nxt;
            }

            if (it == s.end() || it->first > e.max_y) {
                s.insert({e.max_y, tallest});
            }

            s.insert({e.min_y, e.id});
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> w >> h >> n >> m;

    int x_p, y_p;
    cin >> x_p >> y_p;

    int x_s, y_s;
    cin >> x_s >> y_s;
    vector<Event> events;

    int id_s = 0, id_p = 0;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int min_x = min(x1, x2);
        int max_x = max(x1, x2);
        int min_y = min(y1, y2);
        int max_y = max(y1, y2);
        auto inside = [&](int x, int y) {
            return x > min_x && x < max_x && y > min_y && y < max_y;
        };

        if (inside(x_p, y_p)) id_p = i;
        if (inside(x_s, y_s)) id_s = i;

        events.push_back({min_x, max_x, min_y, max_y, i});
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        events.push_back({x, x, y, y, 0});
    }

    make_edges(events);
    for (auto &e : events) {
        swap(e.min_x, e.min_y);
        swap(e.max_x, e.max_y);
    }
    make_edges(events);

    queue<int> q;
    q.push(id_p);
    ban[0] = true;
    ban[id_p] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (!ban[u]) {
                ban[u] = true;
                dis[u] = dis[v] + 1;
                q.push(u);
            }
        }
    }

    cout << dis[id_s] + 1 << "\n";
}