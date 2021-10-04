#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	int n;
	cin >> n;
	vector<int> a(n), b(n), c(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (auto& x : c) cin >> x;
	auto parametric = [&](auto lo, auto hi) {
		auto f = [&](auto mid) -> bool {
			int64_t base = b[0];
			for (int i = 0; i < n; ++i) {
				base += a[i];
				if (base + c[i] >= mid) {
					if (i == n - 1) return true;
					if (base < b[i + 1]) {
						base = b[i + 1];
					}
				}
			}
			return false;
		};
		// // last true
		while (lo != hi) {
			auto mid = lo + (hi - lo + 1) / 2;
			f(mid) ? lo = mid : hi = mid - 1;
		}
		return lo;
	};
	int64_t lo = -3e9, hi = 2e14 + 2e9;
	cout << parametric(lo, hi);
}