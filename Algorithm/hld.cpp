int t, sz[max_N], par[max_N], top[max_N], idx[max_N];

int dfs(int u, int p) {
	for (int& v : adj[u])
		if (v ^ p)
			sz[u] += dfs(v, u);
	return ++sz[u];
}
void hld(int u, int p) {
	int H = 0;
	for (int& v : adj[u])
		if (v ^ p && sz[v] > sz[H])
			H = v;
	for (int& v : adj[u])
		if (v ^ p && v ^ H)
			hld(v, u);

	if (!top[u]) top[u] = u;
	if (H) top[H] = top[u], hld(H, u);

	par[u] = p, idx[u] = ++t;
}