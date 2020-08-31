#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	map<int, int> mp;
	map<int, int>::iterator it;

	for (int q, k, p;;) {
		cin >> q;
		switch (q) {
		case 1:
			cin >> k >> p;
			mp[p] = k;
			break;
		case 2:
			if (mp.empty()) cout << 0 << '\n';
			else {
				it = mp.end(); --it;
				cout << it->second << '\n';
				mp.erase(it);
			}
			break;
		case 3:
			if (mp.empty()) cout << 0 << '\n';
			else {
				it = mp.begin();
				cout << it->second << '\n';
				mp.erase(it);
			}
			break;
		default: return 0;
		}
	}
}