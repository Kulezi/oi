// Rozwiązanie do zadania 'Lunatyk' z II etapu VI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(k^2)
// Złożoność pamięciowa: O(k)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <int BASE>
struct Bignum {
    deque<int> digits;
    Bignum() : digits({0}) {}
    Bignum(int x) : digits({}) {
        if (x == 0) {
            digits = {0};
            return;
        }

        while (x > 0) {
            digits.push_front(x % BASE);
            x /= BASE;
        }
    }

    Bignum operator<<(int n) {
        Bignum res = *this;
        if (res.digits == deque<int>{0}) return res;
        while (n--) {
            res.digits.push_back(0);
        }
        return res;
    }

    Bignum operator>>(int n) {
        Bignum res = *this;
        while (n--) {
            if (res.digits.empty()) break;
            res.digits.pop_back();
        }

        if (res.digits.empty()) res.digits = {0};
        return res;
    }

    Bignum operator+(Bignum rhs) {
        Bignum res = *this;
        int l = res.digits.size() - 1;
        int r = rhs.digits.size() - 1;
        int carry = 0;
        while (r >= 0 || carry > 0) {
            int d = (l < 0 ? 0 : res.digits[l]) + (r < 0 ? 0 : rhs.digits[r]) + carry;
            if (d >= BASE) {
                d -= BASE;
                carry = 1;
            } else {
                carry = 0;
            }

            if (l < 0)
                res.digits.push_front(d);
            else
                res.digits[l] = d;
            l--, r--;
        }


        return res;
    }

    // Zakłada this >= rhs.
    Bignum operator-(Bignum rhs) {
        Bignum res = *this;
        int l = res.digits.size() - 1;
        int r = rhs.digits.size() - 1;
        assert(l >= r);
        int take = 0;
        while (r >= 0 || take > 0) {
            int d = res.digits[l] - (r < 0 ? 0 : rhs.digits[r]) - take;
            if (d < 0) {
                d += BASE;
                take = 1;
            } else {
                take = 0;
            }

            res.digits[l] = d;
            l--, r--;
        }

        while (res.digits.front() == 0 && res.digits.size() > 1) res.digits.pop_front();
        return res;
    }

    operator int() const {
        int res = 0;
        for (auto i : digits) {
            res *= BASE;
            res += i;
        }

        return res;
    }

    // Mnożymy tylko przez stałe <= 10, więc będzie szybkie.
    Bignum operator*(int c) {
        Bignum res = 0;
        while (c--) {
            res = res + *this;
        }
        return res;
    }

    static Bignum read() {
        string n;
        cin >> n;

        Bignum res = 0;
        for (auto c : n) {
            int d = c - '0';
            res = res * 10 + Bignum(d);
        }

        res = res - Bignum(1);
        return res;
    }
};


using Ternary = Bignum<3>;
using Decimal = Bignum<10>;
ostream &operator<<(ostream &os, const Decimal &n) {
    string s;
    for (auto i : n.digits) s += (char)(i + '0');
    return os << s;
}

Ternary ord[3][3] = {{0, 7, 8}, {1, 6, 5}, {2, 3, 4}};
string trans = "aadddcbbd";
Ternary id(Ternary x, Ternary y, int k, Ternary quad_len) {
    if (k == 0) return ord[x][y];

    // Obetnij wspolrzedne do tego kwadratu.
    Ternary quad_x = x >> k;
    Ternary quad_y = y >> k;
    x = x - (quad_x << k);

    y = y - (quad_y << k);
    int quad = ord[quad_x][quad_y];

    // W zależności od współrzędnej obróć / zamień miejscami.
    switch (trans[quad]) {
        case 'a':
            swap(x, y);
            break;
        case 'b':
            swap(x, y);
        case 'c':
            x = (quad_len - x) - Ternary(1);
            y = (quad_len - y) - Ternary(1);
            break;
    }

    Ternary res = id(x, y, k - 1, quad_len >> 1);
    while (quad--) {
        res = res + (quad_len << k);
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);

    int k;
    cin >> k;

    Ternary src_x = Ternary::read(), src_y = Ternary::read();
    Ternary dst_x = Ternary::read(), dst_y = Ternary::read();

    Ternary pow3 = Ternary(1) << (k - 1);

    Ternary ans_ternary = id(dst_x, dst_y, k - 1, pow3) - id(src_x, src_y, k - 1, pow3);
    Decimal ans_decimal(0);
    Decimal pow3_decimal(1);
    for (int i = ans_ternary.digits.size() - 1; i >= 0; i--) {
        ans_decimal = ans_decimal + pow3_decimal * ans_ternary.digits[i];
        pow3_decimal = pow3_decimal * 3;
    }

    cout << ans_decimal << endl;
}
