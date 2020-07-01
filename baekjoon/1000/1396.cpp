#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

struct _edge {
	int u, v, w;
};

const int MAX = 100000;

int N, M, Q;
_edge edge[MAX];
p q[MAX];
vector<int> vt[MAX];
int l[MAX], r[MAX], ans[MAX];
int parent[MAX];

int _find(int u) {
	if (parent[u] < 0) return u;
	return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
	u = _find(u), v = _find(v);
	if (u ^ v) {
		if (parent[u] < parent[v]) swap(u, v);
		parent[v] += parent[u];
		parent[u] = v;
	}
}
bool go() {
	memset(parent, -1, sizeof(int) * N);
	loop(i, M) vt[i].clear();

	bool ret = false;
	loop(i, Q) if (l[i] ^ r[i]) {
		vt[(l[i] + r[i]) >> 1].emplace_back(i);
		ret = true;
	}
	return ret;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> N >> M;
	loop(i, M) {
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
		if (--edge[i].u == --edge[i].v) --i, --M;
	}
	sort(edge, edge + M, [] (auto & a, auto & b) -> bool {
		return a.w < b.w;
	});

	cin >> Q;
	loop(i, Q) {
		cin >> q[i].first >> q[i].second;
		--q[i].first, --q[i].second;
	}

	fill(r, r + Q, M);
	while (go()) loop(m, M) {
		_union(edge[m].u, edge[m].v);
		for (int& i : vt[m]) {
			int u = _find(q[i].first), v = _find(q[i].second);
			if (u == v) {
				r[i] = m;
				ans[i] = -parent[u];
			}
			else l[i] = m + 1;
		}
	}

	loop(i, Q) {
		if (ans[i]) cout << edge[l[i]].w << ' ' << ans[i];
		else cout << -1;
		cout << '\n';
	}
	return 0;
}