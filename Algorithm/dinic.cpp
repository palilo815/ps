#include <bits/stdc++.h>
using namespace std;
struct edge {
	int v, capa, rev;
	edge(int v, int capa, int rev) : v(v), capa(capa), rev(rev) {}
};

const int M = 400;

vector<edge> adj[M];
int level[M], ptr[M];

void add_edge(int u, int v) {
	adj[u].emplace_back(v, 1, adj[v].size());
	adj[v].emplace_back(u, 0, adj[u].size() - 1);
}
int bfs() {
	memset(level, -1, sizeof(level));
	level[0] = 0;

	queue<int> q;
	q.emplace(0);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto& [v, capa, _] : adj[u])
			if (capa && level[v] == -1) {
				level[v] = level[u] + 1;
				q.emplace(v);
			}
	}
	return ~level[1];
}
int dfs(int u) {
	if (u == 1) return 1;
	for (int& i = ptr[u], sz = adj[u].size(); i ^ sz; ++i) {
		auto& [v, capa, rev] = adj[u][i];
		if (capa && level[u] + 1 == level[v])
			if (dfs(v)) {
				--capa, ++adj[v][rev].capa;
				return 1;
			}
	}
	return 0;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, M; cin >> N >> M;
	for (int i = 0, u, v; i ^ M; ++i) {
		cin >> u >> v;
		add_edge(--u, --v);
	}

	int f = 0;
	for (; bfs();) {
		memset(ptr, 0, sizeof(ptr));
		while (dfs(0)) ++f;
	}
	cout << f;
	return 0;
}