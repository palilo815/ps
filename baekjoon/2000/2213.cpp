#include <bits/stdc++.h>
using namespace std;

const int max_N = 1e4 + 1;

vector<int> adj[max_N];
vector<int> ans;
int w[max_N];
int dp[max_N][2];

int solve(int u, int p, int p_used) {
    int& A = dp[u][0];
    if (A == -1) {
        A = 0;
        for (int& v : adj[u])
            if (v ^ p) A += solve(v, u, 0);
    }
    if (p_used) return A;

    int& B = dp[u][1];
    if (B == -1) {
        B = w[u];
        for (int& v : adj[u])
            if (v ^ p) B += solve(v, u, 1);
    }
    return max(A, B);
}
void find_ans(int u, int p, int p_used) {
    if (p_used) {
        for (int& v : adj[u])
            if (v ^ p) find_ans(v, u, 0);
    }
    else {
        if (dp[u][1] > dp[u][0]) {
            ans.emplace_back(u);
            p_used = 1;
        }
        for (int& v : adj[u])
            if (v ^ p) find_ans(v, u, p_used);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> w[i];
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(1, 0, 0) << '\n';

    find_ans(1, 0, 0);
    sort(ans.begin(), ans.end());
    for (int& x : ans) cout << x << ' ';
    return 0;
}