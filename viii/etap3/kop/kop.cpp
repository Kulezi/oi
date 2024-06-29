// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(max(x_i, y_i)))
// Złożoność pamięciowa: O(n + max(x_i, y_i))
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_COORD = 30'000, MAX_X = 2*MAX_COORD + 5;
struct Event {
    int l, r, delta;
};

vector<Event> events[MAX_X];

int n;
int lazy[4 * MAX_X], mx[4 * MAX_X];
void add(int ql, int qr, int delta, int pos = 1, int l = 1, int r = 2*MAX_COORD) {
    if (lazy[pos]) {
        mx[pos] += lazy[pos];
        if (l != r) {
            lazy[pos * 2] += lazy[pos];
            lazy[pos * 2 + 1] += lazy[pos];
        }

        lazy[pos] = 0;
    }

    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        mx[pos] += delta;
        if (l != r) {
            lazy[pos * 2] += delta;
            lazy[pos * 2 + 1] += delta;
        }

        return;
    }

    int m = (l + r) / 2;
    add(ql, qr, delta, pos * 2, l, m);
    add(ql, qr, delta, pos * 2 + 1, m+1, r);
    mx[pos] = max(mx[pos * 2], mx[pos * 2 + 1]);
}

int get_max() {
    return mx[1];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int s, w;
    cin >> s >> w;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        x += MAX_COORD;
        y += MAX_COORD;

        int smallest_x = max(0, x - s);
        int smallest_y = max(0, y - w);

        events[smallest_x].push_back(Event{smallest_y, y, 1});
        events[x+1].push_back(Event{smallest_y, y, -1});
    }


    int ans = 0;
    for (int x = 0; x < MAX_X; x++) {
        for (auto event : events[x]) {
            add(event.l, event.r, event.delta);
        }

        ans = max(ans, get_max());
    }

    cout << ans << "\n";
}