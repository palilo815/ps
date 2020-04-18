#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;
const int INF = 0x3f3f3f3f;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
int parent[max_N + 1];

int Dijkstra(int N, int record) {
	memset(dist, 0x3f, sizeof(int) * (N + 1));
	dist[1] = 0;

	priority_queue<p, vector<p>, greater<p>> pq;
	pq.emplace(0, 1);

	while (1) {
		auto [d, u] = pq.top(); pq.pop();
		if (dist[u] < d) continue;
		if (u == N) return d;

		for (auto [w, v] : adj[u]) {
			int D = d + w;
			if (dist[v] > D) {
				dist[v] = D;
				pq.emplace(D, v);
				if (record) parent[v] = u;
			}
		}
	}
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, M; cin >> N >> M;
	while (M--) {
		int u, v, w; cin >> u >> v >> w;
		adj[u].emplace_back(w, v);
		adj[v].emplace_back(w, u);
	}

	Dijkstra(N, 1);

	int ans = dist[N];
	for (int v = N; parent[v]; v = parent[v]) {
		int u = parent[v];
		for (auto& [w1, n1] : adj[u]) if (n1 == v) {
			for (auto& [w2, n2] : adj[v]) if (n2 == u) {
				int tmp1 = w1, tmp2 = w2;
				w1 = w2 = INF;
				ans = max(ans, Dijkstra(N, 0));
				w1 = tmp1, w2 = tmp2;
				goto OUT;
			}
		}
	OUT:;
	}
	cout << ans;
	return 0;
}