#include <iostream>
using namespace std;

bool dobry(int m, int x_min, int x_max) {
    return x_min + (m - (x_min % m)) % m <= x_max;
}

int najwiekszy(int s_min, int s_max, int w_min, int w_max) {
    for (int m = min(s_max, w_max); m >= 2; m--) {
        if (dobry(m, s_min, s_max) && dobry(m, w_min, w_max)) {
            return m;
        }
    }

    return 1;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    while (n--) {
        int s_min, s_max, w_min, w_max;
        cin >> s_min >> s_max >> w_min >> w_max;
        cout << najwiekszy(s_min, s_max, w_min, w_max) << "\n";
    }
}