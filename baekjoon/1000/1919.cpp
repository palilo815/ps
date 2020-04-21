#include <iostream>
using namespace std;

int cnt[2][26];
int main() {
	string s1, s2; cin >> s1 >> s2;
	for (char c : s1) ++cnt[0][c - 'a'];
	for (char c : s2) ++cnt[1][c - 'a'];
	int ans = 0;
	for (int i = 0; i < 26; i++)
		ans += abs(cnt[0][i] - cnt[1][i]);
	cout << ans;
	return 0;
}