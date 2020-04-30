#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_W = 1000;

int x[max_W + 2], y[max_W + 2];
int DP[max_W + 2][max_W + 2];
int parent[max_W + 2][max_W + 2];

int dist(int a, int b) {
	return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	memset(DP, 0x3f, sizeof(DP));
	DP[0][1] = 0;

	int N, W; cin >> N >> W;
	x[0] = y[0] = 1;
	x[1] = y[1] = N;
	for (int i = 2; i < W + 2; ++i) {
		cin >> x[i] >> y[i];
		int d1 = dist(i, i - 1);
		for (int j = 0; j < i - 1; ++j) {
			int d2 = dist(i, j);
			if (DP[i - 1][j] + d1 < DP[i][j]) {
				DP[i][j] = DP[i - 1][j] + d1;
				parent[i][j] = -1;
			}
			if (DP[j][i - 1] + d1 < DP[j][i]) {
				DP[j][i] = DP[j][i - 1] + d1;
				parent[j][i] = 1;
			}
			if (DP[j][i - 1] + d2 < DP[i][i - 1]) {
				DP[i][i - 1] = DP[j][i - 1] + d2;
				parent[i][i - 1] = j - i;
			}
			if (DP[i - 1][j] + d2 < DP[i - 1][i]) {
				DP[i - 1][i] = DP[i - 1][j] + d2;
				parent[i - 1][i] = i - j;
			}
		}
	}
	int ans = INT_MAX;
	int a, b;
	for (int i = 0; i < W + 1; ++i) {
		if (ans > DP[i][W + 1]) ans = DP[i][W + 1], a = i, b = W + 1;
		if (ans > DP[W + 1][i]) ans = DP[W + 1][i], a = W + 1, b = i;
	}

	cout << ans;
	stack<int> path;
	while (a != 0 || b != 1) {
		int cnt = parent[a][b];
		if (cnt < 0) {
			a += cnt;
			path.emplace(1);
		}
		else if (cnt > 0) {
			b -= cnt;
			path.emplace(2);
		}
	}
	while (!path.empty()) {
		cout << '\n' << path.top();
		path.pop();
	}
	return 0;
}