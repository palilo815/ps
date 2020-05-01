#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000000;

char s[max_N * 2 + 1];
int p[max_N * 2 + 1];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	string ori; cin >> ori;
	int N = 1;
	for (char c : ori) {
		s[N] = c;
		N += 2;
	}

	int l = 0, r = -1;
	for (int i = 0; i < N; ++i) {
		int k;
		if (i > r) k = 0;
		else k = min(p[l + r - i], r - i);

		while (i - k > 0 && i + k < N - 1 && s[i - k - 1] == s[i + k + 1])
			++k;

		p[i] = k;
		if (i + k > r)
			l = i - k, r = i + k;
	}

	long long ans = 0;
	for (int i = 0; i < N; ++i)
		ans += (p[i] + 1) / 2;
	cout << ans;
	return 0;
}