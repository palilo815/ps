#include <cstdio>
typedef long long ll;

ll x[4], y[4];
int ccw(int i1, int i2, int i3) {
	ll ret = (x[i1] * y[i2] + x[i2] * y[i3] + x[i3] * y[i1]) -
		(y[i1] * x[i2] + y[i2] * x[i3] + y[i3] * x[i1]);
	if (ret > 0) return 1;
	else if (ret < 0) return -1;
	return 0;
}
int inside(int i1, int m, int i2) {
	ll xl, xr, yd, yu;
	if (x[i1] < x[i2])
		xl = x[i1], xr = x[i2];
	else
		xl = x[i2], xr = x[i1];
	if (y[i1] < y[i2])
		yd = y[i1], yu = y[i2];
	else
		yd = y[i2], yu = y[i1];
	return xl <= x[m] && x[m] <= xr && yd <= y[m] && y[m] <= yu;
}
int main() {
	for (int i = 0; i < 4; ++i)
		scanf("%lld %lld", &x[i], &y[i]);

	int c1 = ccw(0, 1, 2), c2 = ccw(0, 1, 3);
	if ((c1 == 0 && inside(0, 2, 1)) || (c2 == 0 && inside(0, 3, 1))) {
		putchar('1');
		return 0;
	}
	int c3 = ccw(2, 3, 0), c4 = ccw(2, 3, 1);
	if ((c3 == 0 && inside(2, 0, 3)) || (c4 == 0 && inside(2, 1, 3))) {
		putchar('1');
		return 0;
	}
	printf("%d", (c1 != c2 && c3 != c4));
	return 0;
}