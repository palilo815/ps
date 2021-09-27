#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
	int n;
	cin >> n;
	vector<pair<int64_t, int64_t>> a(n);
	for (auto& [x, y] : a) {
		cin >> x >> y;
	}
	sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
		return lhs.first < rhs.first;
	});
	vector<int64_t> pref(n + 1);
	for (int i = 0; i < n; ++i) {
		pref[i + 1] = pref[i] + a[i].second;
	}
	int64_t best = a[0].first - pref[0];
	int64_t ans = ~INF;
	for (int r = 1; r <= n; ++r) {
		chmax(ans, pref[r] - a[r - 1].first + best);
		if (r != n) chmax(best, a[r].first - pref[r]);
	}
	cout << ans;
}