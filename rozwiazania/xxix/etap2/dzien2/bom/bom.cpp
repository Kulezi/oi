// Rozwiązanie zadania 'Bomberman' z II Etapu XXIX OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n^2)
// Złożoność pamięciowa: O(n^2)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1005;

vector<pair<int,int>> ruchy = {
    {1,  0},
    {-1, 0},
    {0,  1},
    {0, -1}
};

string s[MAXN];
pair<int,int> P, K;

array<int, 4> from[MAXN][MAXN][3][3];
char kierunek(int x, int y) {
    if (x == 1) return 'D';
    if (x == -1) return 'G';
    if (y == 1) return 'P';
    return 'L';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        for (int j = 1; j <= n; j++) {
            if (s[i][j-1] == 'P') P = {i, j};
            if (s[i][j-1] == 'K') K = {i, j};
        }
    }



    // Idę sobie, nie detonowałem żadnych bomb - w pewnym momencie
    // napotykam zamurowane pole - mogę na nie wejść stawiając bombę:
    // nie muszę decydować gdzie dokładnie - ale muszę zdecydować czy w tej kolumnie
    // czy w wierszu.
    // Wtedy mogę chodzić po cegłach
    // Stan:
    // - gdzie jestem - (x, y)
    // - {0 - mogę zmienić, 1 - chodzę po, 2 - nie mogę zmienić} x na którym stoi bomba.
    // - {0 - mogę zmienić, 1 - chodzę po, 2 - nie mogę zmienić} y na którym stoi bomba.
    
    queue<array<int, 4>> q;
    q.push({P.first, P.second, 0, 0});
    from[P.first][P.second][0][0] = {-1, -1, -1, -1};
    while (!q.empty()) {
        auto [x, y, rx, ry] = q.front();

        if (x == K.first && y == K.second) {
            string res;

            // To wypiszę jak będą bomby wymagające zakrętu na mojej ścieżce.
            int bx = 0, by = 0;
            pair<int,int> bomba;
            while (from[x][y][rx][ry][0] != -1) {
                auto [px, py, prx, pry] = from[x][y][rx][ry];
                if (rx == 1) bx = x;
                if (ry == 1) by = y;
                res += kierunek(x - px, y - py);
                x = px;
                y = py;
                rx = prx;
                ry = pry;
                
                if (s[x][y-1] == '#') bomba = {x, y}; 

            }
            cout << res.size() << "\n";
            // To wypiszę jak wszystkie bomby ze ścieżki są na jednej linii.
            if (!bx || !by) tie(bx, by) = bomba;
            // A to wypiszę jak nie ma żadnej bomby.
            if (!bx || !by) tie(bx, by) = P;
            cout << bx << " " << by << "\n";
            reverse(res.begin(), res.end());
            cout << res << "\n";
            return 0;
        }

        auto relax = [&](int x, int y, int rx, int ry) {
            if (x < 1 || x > n || y < 1 || y > n) return;
            if (s[x][y-1] == 'X') return;
            if (s[x][y-1] == '#' && rx != 1 && ry != 1) return;

            if (!from[x][y][rx][ry][0]) {
                from[x][y][rx][ry] = q.front();
                q.push({x, y, rx, ry});
            }
        };
 
        for (auto [dx, dy] : ruchy) {
            int nx = x + dx;
            int ny = y + dy;
            // Bomby jeszcze nie było.
            if (rx + ry == 0) {
                // Nie stawiam bomby.
                relax(nx, ny, 0, 0);

                // Stawiam bombę (ale tylko na jednym wymiarze).
                relax(nx, ny, 0, 1);
                relax(nx, ny, 1, 0);
            } else if (y != ny) {
                relax(nx, ny, (rx == 0 ? 1 : rx), (ry == 1 ? 2 : ry));
            } else if (x != nx) {
                relax(nx, ny, (rx == 1 ? 2 : rx), (ry == 0 ? 1 : ry));
            }
        }
        q.pop();
    }

    cout << "NIE\n";
}
