#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

//cost : 건물 짓는 시간, Pre : 먼저 지어놔야 하는 건물 개수
int V, Cost[1001], Pre[1001];
vector<int> adj[1001];

int main()
{
	cin.tie(NULL), cout.tie(NULL);
	ios::sync_with_stdio(false);

	int t, E, goal;
	cin >> t;
	while (t-- > 0) {
		for (auto& v : adj) v.clear();
		memset(Pre, 0, sizeof(Pre));

		cin >> V >> E;
		for (int i = 1; i <= V; ++i) cin >> Cost[i];
		while (E-- > 0) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			Pre[v]++;
		}

		cin >> goal;
		priority_queue<P, vector<P>, greater<P>> pq;
		// !Pre[i] == i를 짓기 위해 필요한 테크 건물들을 다 지었다.
		// pq에 건설 가능한 건물들을 넣는다.
		for (int i = 1; i <= V; ++i)
			if (!Pre[i]) pq.push(make_pair(Cost[i], i));
		while (1) {
			// 지금 지은 건물은 build, 현재 시각 T
			int T = pq.top().first, build = pq.top().second; pq.pop();
			// 목표 건물 goal을 지으면 끝
			if (build == goal) { cout << T << '\n'; break; }

			// bulid를 지음으로써 추가로 건설 가능한 건물들을 pq에 추가
			loop(i, adj[build].size()) {
				int next = adj[build][i];
				Pre[next]--;
				if (!Pre[next]) {
					int nextT = T + Cost[next];
					pq.push(make_pair(nextT, next));
				}
			}
		}
	}
	return 0;
}