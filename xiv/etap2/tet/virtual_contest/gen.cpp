#include <bits/stdc++.h>
using namespace std;

bool has_neighboring(vector<int> v) {
    for (int i = 0; i + 1 < v.size(); i++) {
        if (v[i] == v[i + 1]) return true;
    }

    return false;
}

int32_t main() {
    srand(chrono::steady_clock::now().time_since_epoch().count());
    int n = 6;

    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
        v.push_back(i);
    }

    // while ma dwa sasiadujace szufla.
    do {
        random_shuffle(v.begin(), v.end());
    } while (has_neighboring(v));

    cout << n << "\n";
    for (auto i : v) {
        cout << i << " ";
    }
    cout << "\n";
}


