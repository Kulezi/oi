#include <bits/stdc++.h>
using namespace std;

map<vector<int>, vector<int>> vis;

void ztetrisuj(vector<int> &v) {
    vector<int> nowy;
    for (auto i : v) {
        if (!nowy.empty() && i == nowy.back()) nowy.pop_back();
        else nowy.push_back(i);
    }

    v = nowy;
}

int verify(string name, vector<int> t, ifstream &input) {
    int m;
    input >> m;

    cerr << name << "\nini: [";
    for (auto j : t) {
        cerr << j << " ";
    }cerr << "]\n";

    for (int i = 1; i <= m; i++) {
        int idx;
        input >> idx;
        cerr << idx << " -> [";
        swap(t[idx-1], t[idx]);
        ztetrisuj(t);

        for (auto j : t) {
            cerr << j << " ";
        }cerr << "]\n";
    }cerr << "\n";

    if (t.size() != 0) {
        cout << name << ": solution doesn't clear the stack" << endl;
        return -(int)name.size();
    }

    return m;
}

int32_t main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);

    assert(argc == 4);
    string testfile = argv[1], brutefile = argv[2], modelfile = argv[3];

    ifstream test(testfile), brute(brutefile), model(modelfile);

    int n;
    test >> n;

    vector<int> t(2 * n);
    for (auto &i : t) test >> i;

    int m_brute = verify("brut", t, brute);
    int m_model = verify("model", t, model);

    if (m_brute != m_model) {
        cout << "solution sizes differ\n";
        cout << "brute found " << m_brute << " != " << m_model << endl;
        return -1;
    }


    return 0;
}