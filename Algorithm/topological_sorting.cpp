vector<int> vt;
vector<bool> visited(N);

function<void(int)> dfs = [&](int u) {
    visited[u] = true;
    for (int& v : adj[u])
        if (!visited[v])
            dfs(v);
    vt.emplace_back(u);
};