#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 5000;

// DP[i][j] = [i,j]수열을 팰린드롬으로 만들기 위해 넣어야 하는 숫자의 최소 개수
int arr[max_N];
int DP[max_N][max_N];

int min(int a, int b) {
	return a < b ? a : b;
}
int main() {
	int N; scanf("%d", &N);
	loop(i, N) scanf("%d", &arr[i]);

	loop(i, N) DP[i][i] = 0;
	loop(i, N - 1) DP[i][i + 1] = (arr[i] != arr[i + 1]);
	
	for (int gap = 2; gap < N; ++gap)
		loop(i, N - gap) {
			int j = i + gap;
			if (arr[i] == arr[j]) DP[i][j] = DP[i + 1][j - 1];
			else DP[i][j] = min(DP[i + 1][j], DP[i][j - 1]) + 1;
		}
	printf("%d", DP[0][N - 1]);
	return 0;
}