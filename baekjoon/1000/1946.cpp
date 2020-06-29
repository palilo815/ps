#include<bits/stdc++.h>
using namespace std;

map<int, int> mp;

bool poor(int a, int b) {
	auto it = mp.lower_bound(a);
	if (it == mp.begin()) return false;
	return b > (--it)->second;
}
void drop(int a, int b) {
	auto it = mp.upper_bound(a);
	for (auto it =  mp.upper_bound(a); it != mp.end(); it = mp.erase(it))
		if (it->second < b)
			break;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T; cin >> T;
	while (T--) {
		mp.clear();
		int N; cin >> N;
		while (N--) {
			int a, b; cin >> a >> b;
			if (poor(a, b)) continue;
			mp[a] = b;
			drop(a, b);
		}
		cout << mp.size() << '\n';
	}
	return 0;
}