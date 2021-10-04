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
	if (n % 2 == 0) {
		if (n == 2) return cout << -1, 0;
		cout << n / 2 << '\n';
		for (int i = 1; i <= n / 2; ++i) {
			cout << 2 << ' ' << 2 * i - 1 << ' ' << 2 * (n - i) + 1 << '\n';
		}
		return 0;
	}
	int a = -1;
	for (int i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			a = i;
			break;
		}
	}
	if (a == -1) return cout << -1, 0;
	vector ans(n / a, vector<int>(a));
	for (int i = 0; i < a; ++i) {
		iota(ans[i].begin(), ans[i].end(), i * a);
		rotate(ans[i].begin(), ans[i].end() - i, ans[i].end());
	}
	for (int i = a; i < n / a; i += 2) {
		iota(ans[i].begin(), ans[i].end(), i * a);
		iota(ans[i + 1].rbegin(), ans[i + 1].rend(), (i + 1) * a);
	}
	cout << a << '\n';
	for (int i = 0; i < a; ++i) {
		cout << n / a;
		for (auto& x : ans) {
			cout << ' ' << 2 * x[i] + 1;
		}
		cout << '\n';
	}
}