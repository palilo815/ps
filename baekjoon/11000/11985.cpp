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
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> a(n);
	for (auto& x : a) {
		cin >> x;
	}
	vector dp(n + 1, INF);
	dp[0] = 0;
	for (int i = 0; i < n; ++i) {
		int mn = INT_MAX, mx = INT_MIN;
		for (int j = i + 1, ed = min(i + m, n); j <= ed; ++j) {
			chmin(mn, a[j - 1]), chmax(mx, a[j - 1]);
			chmin(dp[j], dp[i] + k + int64_t(j - i) * (mx - mn));
		}
	}
	cout << dp.back();
}