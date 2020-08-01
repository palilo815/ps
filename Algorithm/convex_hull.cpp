#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int M = 100000;

p poly[M];

int ccw(p& a, p& b, p& c) {
	ll ret = 1LL * (b.x - a.x) * (c.y - a.y) -
	         1LL * (b.y - a.y) * (c.x - a.x);
	return ret ? (ret > 0 ? 1 : -1) : 0;
}
ll dist(p& v) {
	ll dx = poly[0].x - v.x, dy = poly[0].y - v.y;
	return dx * dx + dy * dy;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N; cin >> N;
	loop(i, N) cin >> poly[i].x >> poly[i].y;

	swap(poly[0], *min_element(poly, poly + N));
	sort(poly + 1, poly + N, [&](p & a, p & b) {
		int ret = ccw(poly[0], a, b);
		return ret ? ret == 1 : dist(a) < dist(b);
	});

	vector<p> hull;
	loop(i, N) {
		while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) <= 0)
			hull.pop_back();
		hull.emplace_back(poly[i]);
	}
	cout << hull.size();
	return 0;
}