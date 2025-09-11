// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n).
// Punkty: 100

#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
basic_string<int> v;
int mult_x, mult_y = 1, n, len, X, Y, i;
ll dx, dy, onecycle, timeleft, cycles, a, ox, oy, res, la, ra, sgn, length, mult;
inline void rotate()
{	swap(mult_x, mult_y);
	mult_y = -mult_y;
}
inline void move()
{	ox += mult_x * v[i]; oy += mult_y * v[i];
	rotate();
}
inline void check(ll &div1, ll &div2, ll len, int &dest, ll left, ll right)
{	a = len / div1;
	if(a < 0 || a >= cycles || (a * div1) != len)return;
	left += a * div2;
	right += a * div2;
	if(left < right && left < dest && right >= dest)res++;
	else if(left > right && left > dest && right <= dest)res++;
}
inline void add(ll left, ll right, ll d, ll dest)
{	la = (dest - left) / d, ra = (dest - right) / d, sgn = 1;
	bool jeden = (d > 0), dwa = (left < right);
	if(dwa == jeden)
		la = min(la, cycles - 1), ra = max(ra, 0LL);
	else la = max(la, 0LL), ra = min(ra, cycles - 1), sgn = -sgn;
	if(dwa && la * d + left >= dest)la -= sgn;
	if(dwa && ra * d + right < dest)ra += sgn;
	if(!dwa && la * d + left <= dest)la -= sgn;
	if(!dwa && ra * d + right > dest)ra += sgn;
	if(dwa != jeden) swap(ra, la);
	res += max(0LL, la - ra + 1);
}
inline void gemacht()
{	if(i % 4 == 0 && ox == X && oy < Y && oy + length >= Y) res++;
	else if(i % 4 == 2 && ox == X && oy > Y && oy - length <= Y) res++;
	else if(i % 4 == 1 && oy == Y && ox < X && ox + length >= X) res++;
	else if(i % 4 == 3 && oy == Y && ox > X && ox - length <= X) res++;
}
inline void consider()
{	mult = ((i % 4 < 2) ? 1 : -1);
	if(dx && i % 2 == 0) check(dx, dy, X - ox, Y, oy, oy + v[i] * mult);
	else if(!dx && i % 2 == 0 && ox == X) add(oy, oy + v[i] * mult, dy, Y);
	else if(dy && i % 2 == 1) check(dy, dx, Y - oy, X, ox, ox + v[i] * mult);
	else if(!dy && i % 2 == 1 && oy == Y)add(ox, ox + v[i] * mult, dx, X);
}
main()
{	ios_base::sync_with_stdio(0);
	cin >> n >> timeleft;
	for(i = 0; i < n; i++)
		cin >> len, v += len;
	cin >> X >> Y;
	while(n % 4 != 0)
		v += v, n += n;
	for(i = 0; i < n; i++)
		dx += mult_x * v[i], dy += mult_y * v[i],
		onecycle += v[i] + 1,
		rotate();
	cycles = timeleft / onecycle;
	if(dx != 0 || dy != 0)
		for(i = 0; i < n; i++) consider(), move();
	if(!dx && !dy)
	{	for(i = 0; i < n; i++)
			length = v[i],
			gemacht(),
			move();
		res *= cycles;
	}
	if(!cycles)res = 0;
	ox = dx * cycles, oy = dy * cycles;
	timeleft %= onecycle;
	for(i = 0; i < n && timeleft > 0; i++)
		length = min((ll)v[i], timeleft),
		gemacht(),
		timeleft -= v[i] + 1,
		move();
	if(X == 0 && Y == 0)res++;
	cout << res;
}