#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 100;
const int max_M = 10000;

vector<tup> adj[max_N + 1];
p min_t[max_N + 1];
p min_m[max_N + 1];

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N, T, M, L;
	cin >> N >> T >> M >> L;
	while (L--) {
		int u, v, t, m;
		cin >> u >> v >> t >> m;
		adj[u].emplace_back(m, t, v);
		adj[v].emplace_back(m, t, u);
	}

	fill_n(min_t + 2, N - 1, make_pair(T, M));
	fill_n(min_m + 2, N - 1, make_pair(M, T));

	priority_queue<tup, vector<tup>, greater<tup>>pq;
	pq.emplace(0, 0, 1);

	while (!pq.empty()) {
		auto [m_u, t_u, u] = pq.top(); pq.pop();
		if (u == N) { cout << m_u; return 0; }

		for (auto [m, t, v] : adj[u]) {
			int m_v = m + m_u, t_v = t + t_u, flag = 0;
			if (m_v > M || t_v > T) continue;

			p new_t = { t_v,m_v };
			p new_m = { m_v,t_v };
			if (new_t < min_t[v]) min_t[v] = new_t, flag = 1;
			if (new_m < min_m[v]) min_m[v] = new_m, flag = 1;
			if (flag) pq.emplace(m_v, t_v, v);
		}
	}
	cout << -1;
	return 0;
}