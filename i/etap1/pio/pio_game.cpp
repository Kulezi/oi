// Gra pozwalająca na testowanie rozwiązań do zadania 'Pionki' z I etapu I OI.
// Autor: Paweł Putra

#include <bits/stdc++.h>
#include <termios.h>
using namespace std;
constexpr int N = 2;
int t[N][N];

void flip(int x, int y) {
    for (int delta_x = -1; delta_x <= 1; delta_x++) {
        for (int delta_y = -1; delta_y <= 1; delta_y++) {
            if (delta_x == 0 && delta_y == 0) continue;
            int nx = x + delta_x;
            int ny = y + delta_y;
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            t[nx][ny] = 1 - t[nx][ny];
        }
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return (buf);
}

int caret_x = 0, caret_y = 0;
void print_board() {
    system("clear");
    cout << caret_x << " " << caret_y << endl;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (x == caret_x && y == caret_y) {
                cout << "X";
            } else {
                if (t[x][y])
                    cout << '#';
                else
                    cout << '.';
            }
        }
        cout << endl;
    }
}

int32_t main() {
    while (1) {
        char c = getch();
        fflush(stdin);
        cout << (int)c << endl;
        switch (c) {
            case ' ':
                flip(caret_x, caret_y);
                break;
            case 'a':
                caret_y--;
                break;
            case 'd':
                caret_y++;
                break;
            case 'w':
                caret_x--;
                break;
            case 's':
                caret_x++;
                break;
        }

        caret_x = clamp(caret_x, 0, N - 1);
        caret_y = clamp(caret_y, 0, N - 1);

        print_board();
    }
}