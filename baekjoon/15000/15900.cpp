#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5 + 1;
const string ans[2] = {"No", "Yes"};

vector<int> adj[mxN];
int sum;

void solve(int u, int p, int d) {
    if (adj[u].size() == 1) sum ^= d;
    for (int& v : adj[u])
        if (v ^ p)
            solve(v, u, d + 1);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int u, v; --N;) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    adj[1].emplace_back(0);
    solve(1, 0, 0);

    cout << ans[sum & 1];
    return 0;
}