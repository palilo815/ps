#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using p = pair<int, int>;

const int mx = 1e5 + 1;

vector<p> adj[mx];
int t, sz[mx], par[mx], top[mx], dist[mx], idx[mx];
int minT[mx << 1], maxT[mx << 1];

void dfs(int u, int p) {
	par[u] = p, sz[u] = 1;
	for (auto& [w, v] : adj[u])
		if (v ^ p) {
			dfs(v, u);
			dist[v] = w;
			sz[u] += sz[v];
		}
}
void hld(int u, int p) {
	int H = 0;
	for (auto& [_, v] : adj[u])
		if (v ^ p && sz[v] > sz[H])
			H = v;
	for (auto& [_, v] : adj[u])
		if (v ^ p && v ^ H)
			hld(v, u);

	if (!top[u]) top[u] = u;
	if (H) top[H] = top[u], hld(H, u);

	par[u] = p, idx[u] = t++;
}
int mn_query(int l, int r) {
	int ret = INT_MAX;
	for (l += t, r += t; l ^ r; l >>= 1, r >>= 1) {
		if (l & 1) ret = min(ret, minT[l++]);
		if (r & 1) ret = min(ret, minT[--r]);
	}
	return ret;
}
int mx_query(int l, int r) {
	int ret = INT_MIN;
	for (l += t, r += t; l ^ r; l >>= 1, r >>= 1) {
		if (l & 1) ret = max(ret, maxT[l++]);
		if (r & 1) ret = max(ret, maxT[--r]);
	}
	return ret;
}
void solve(int u, int v) {
	int x = INT_MAX, y = INT_MIN;
	while (top[u] ^ top[v]) {
		int& n = sz[top[u]] < sz[top[v]] ? u : v;
		x = min(x, mn_query(idx[n], idx[top[n]] + 1));
		y = max(y, mx_query(idx[n], idx[top[n]] + 1));
		n = par[top[n]];
	}
	if (idx[u] > idx[v]) swap(u, v);
	x = min(x, mn_query(idx[u], idx[v]));
	y = max(y, mx_query(idx[u], idx[v]));
	cout << x << ' ' << y << '\n';
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int N; cin >> N;
	for (int i = 1, u, v, w; i < N; ++i) {
		cin >> u >> v >> w;
		adj[u].emplace_back(w, v);
		adj[v].emplace_back(w, u);
	}

	dfs(1, 0);
	hld(1, 0);

	for (int i = 1; i <= N; ++i)
		minT[t + idx[i]] = maxT[t + idx[i]] = dist[i];
	for (int i = t - 1; i; --i) {
		minT[i] = min(minT[left], minT[right]);
		maxT[i] = max(maxT[left], maxT[right]);
	}

	int Q; cin >> Q;
	for (int u, v; Q--;) {
		cin >> u >> v;
		solve(u, v);
	}
	return 0;
}