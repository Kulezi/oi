#include <bits/stdc++.h>
using namespace std;
int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
int32_t main() {
    int n = R(2, 1000);
    cout << n << endl;
    while (n--) {
        int pol = R(1, 5);
        string polowa;
        while (pol--) polowa += (char)R('a', 'b');
        string s = polowa;
        if (R(0, 1)) s += (int)R('a', 'c');
        reverse(polowa.begin(), polowa.end());
        s += polowa;
        cout << s.size() << " " << s << endl;
    }
}