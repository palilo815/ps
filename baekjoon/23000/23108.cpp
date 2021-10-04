#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	vector<int> a(n - 1), b(m), c(n), d(m - 1);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (auto& x : c) cin >> x;
	for (auto& x : d) cin >> x;
	int64_t ans = accumulate(a.begin(), a.end(), 0ll) + b[0] * int64_t(n - 1) +
				  accumulate(d.begin(), d.end(), 0ll) + c[0] * int64_t(m - 1) +
				  accumulate(b.begin() + 1, b.end(), 0ll) * int64_t(n - 1);
	transform(d.begin(), d.end(), b.begin() + 1, d.begin(), minus());
	sort(d.begin(), d.end());
	vector<int64_t> pref(m);
	for (int i = 0; i < m - 1; ++i) {
		pref[i + 1] = pref[i] + d[i];
	}
	for (int i = 1; i < n; ++i) {
		const auto lo = lower_bound(d.begin(), d.end(), a[i - 1] - c[i]) - d.begin();
		ans += pref[lo] + (d.size() - lo) * a[i - 1] + lo * c[i];
	}
	cout << ans;
}