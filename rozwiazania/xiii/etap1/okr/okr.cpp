// Rozwiązanie do zadania 'Okresy słów' z I etapu XIII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    string s;
    cin >> n >> s;

    // Utrzymują długość najdłuższego i najkrótszego niepustego prefiksosufiksu
    // dla prefiksu długości i.
    vector<int> longest(n + 1, 0), shortest(n + 1, 0);
    longest[0] = -1;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int zgodne = longest[i - 1];
        while (zgodne != -1 && s[zgodne] != s[i - 1]) zgodne = longest[zgodne];
        longest[i] = zgodne + 1;

        shortest[i] = longest[i];
        if (longest[longest[i]] > 0) shortest[i] = shortest[longest[i]];
        if (shortest[i] > 0) ans += i - shortest[i];
    }

    cout << ans << "\n";
}