#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1001;

vector<p> adj[max_N];
priority_queue<int> dist[max_N];
int cnt;

void print_ans(int& K) {
	if (dist[1].empty()) return;
	int x = dist[1].top(); dist[1].pop();
	print_ans(--K);
	cout << x << '\n';
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, M, K; cin >> N >> M >> K;
	while (M--) {
		int u, v, w; cin >> u >> v >> w;
		adj[u].emplace_back(w, v);
	}

	dist[N].emplace(0);

	priority_queue<p, vector<p>, greater<p>> pq;
	pq.emplace(0, N);

	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (dist[u].top() < d) continue;

		for (auto [w, v] : adj[u]) {
			int D = d + w;
			if (dist[v].size() < K) {
				dist[v].emplace(D);
				pq.emplace(D, v);
			}
			else if (dist[v].top() > D) {
				dist[v].pop();
				dist[v].emplace(D);
				pq.emplace(D, v);
			}
		}
	}
	print_ans(K);
	while (K--) cout << -1 << '\n';
	return 0;
}