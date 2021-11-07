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
	vector<int> cnt(m);
	queue<pair<int, int>> q;
	for (int p, w; n--;) {
		cin >> p >> w, --p;
		++cnt[p];
		q.emplace(p, w);
	}
	int ans = 0, target = m - 1;
	vector<int> boxes;
	while (!q.empty()) {
		const auto [p, w] = q.front();
		q.pop();
		ans += w;
		if (p != target) {
			q.emplace(p, w);
			continue;
		}
		for (const auto& box : boxes) {
			if (box < w) {
				ans += box * 2;
			}
		}
		boxes.emplace_back(w);
		if (--cnt[target] == 0) {
			--target;
			boxes.clear();
		}
	}
	cout << ans;
}
