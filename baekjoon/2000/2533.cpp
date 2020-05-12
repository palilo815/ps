#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000001;

vector<int> adj[max_N];
int DP[max_N][2];

int solve(int u, int p, int early) {
	int& ret = DP[u][early];
	if (ret != -1) return ret;

	ret = 0;
	if (early) {
		for (int v : adj[u]) if (v != p)
			ret += min(solve(v, u, 0), solve(v, u, 1));
		++ret;
	}
	else for (int v : adj[u]) if (v != p)
		ret += solve(v, u, 1);
	return ret;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N; cin >> N;
	while (--N) {
		int u, v; cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	memset(DP, -1, sizeof(DP));
	cout << min(solve(1, 0, 0), solve(1, 0, 1));
	return 0;
}