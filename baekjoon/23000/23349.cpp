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
	int n;
	cin >> n;
	string name, place;
	unordered_set<string> checked;
	map<string, pair<vector<int>, vector<int>>> intervals;
	for (int l, r; n--;) {
		cin >> name >> place >> l >> r;
		if (checked.emplace(name).second) {
			intervals[place].first.emplace_back(l);
			intervals[place].second.emplace_back(r);
		}
	}
	for_each(intervals.begin(), intervals.end(), [&](auto& x) {
		sort(x.second.first.begin(), x.second.first.end());
		sort(x.second.second.begin(), x.second.second.end());
	});
	int mx = 0;
	pair busy_interval(-1, -1);
	for (const auto& [where, lr] : intervals) {
		int cnt = 0;
		for (auto l = lr.first.begin(), r = lr.second.begin(); r != lr.second.end();) {
			if (l != lr.first.end() && *l < *r) {
				if (chmax(mx, ++cnt)) {
					place = where;
					busy_interval = {*l, -1};
				}
				++l;
			} else {
				if (busy_interval.second == -1) {
					busy_interval.second = *r;
				}
				++r, --cnt;
			}
		}
	}
	cout << place << ' ' << busy_interval.first << ' ' << busy_interval.second;
}