#include <cstdio>

const int MAX = 100;
const int mod = 100000;
const int ver = 0;
const int hor = 1;

int DP[MAX][MAX][2];

int main() {
	int col, row; scanf("%d %d", &col, &row);
	for (int r = 0; r < row; ++r)
		DP[r][0][ver] = 1;
	for (int c = 0; c < col; ++c)
		DP[0][c][hor] = 1;

	for (int r = 1; r < row; ++r)
		for (int c = 1; c < col; ++c) {
			DP[r][c][ver] = (DP[r - 1][c][ver] + DP[r - 1][c - 1][hor]) % mod;
			DP[r][c][hor] = (DP[r][c - 1][hor] + DP[r - 1][c - 1][ver]) % mod;

		}

	int ans = DP[row - 1][col - 1][ver] + DP[row - 1][col - 1][hor];
	printf("%d", ans % mod);
	return 0;
}