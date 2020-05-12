#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 30;
const int INF = 0x3f3f3f3f;

int DP[max_N][max_N];
int tmp[max_N][max_N];

int adj[max_N][max_N];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		loop(i, N - 1) for (int j = i + 1; j < N; ++j) {
			cin >> adj[i][j];
			adj[j][i] = adj[i][j];
		}

		loop(k, N) loop(i, k) for (int j = k + 1; j < N; ++j)
			adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

		memset(DP, 0x3f, sizeof(DP));
		DP[0][0] = 0;

		for (int t = 1; t < N; ++t) {
			memset(tmp, 0x3f, sizeof(tmp));
			loop(i, t) loop(j, i + 1) if (DP[i][j] != INF) {
				tmp[i][j] = min(tmp[i][j], DP[i][j] + adj[t - 1][t]);
				tmp[t - 1][i] = min(tmp[t - 1][i], DP[i][j] + adj[j][t]);
				tmp[t - 1][j] = min(tmp[t - 1][j], DP[i][j] + adj[i][t]);
			}
			memcpy(DP, tmp, sizeof(DP));
		}
		cout << *min_element(&DP[0][0], &DP[N][0]) << '\n';
	}
	return 0;
}