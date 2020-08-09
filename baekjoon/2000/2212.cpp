#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1e4;

int a[mx];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, K; cin >> N >> K;
	loop(i, N) cin >> a[i];

	sort(a, a + N);
	N = unique(a, a + N) - a;
	adjacent_difference(a, a + N, a);

	sort(a + 1, a + N);
	N -= K;

	int ans = 0;
	for (int i = 1; i <= N; ++i)
		ans += a[i];
	cout << ans;
	return 0;
}