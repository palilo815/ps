#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
	int ret = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
	return ret ? (ret > 0 ? 1 : -1) : 0;
}
int ccw(p& a, p& b, p& c) {
	int ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return ret ? (ret > 0 ? 1 : -1) : 0;
}
bool cross(p& a, p& b, p& c, p& d) {
	int A = ccw(a, b, c) * ccw(a, b, d);
	int B = ccw(c, d, a) * ccw(c, d, b);
	if (A | B) return A <= 0 && B <= 0;
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return a <= d && c <= b;
}