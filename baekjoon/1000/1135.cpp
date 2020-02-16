#include <bits/stdc++.h>
using namespace std;

const int max_N = 50;

vector<int> adj[max_N];

// solve(u) : u가 자신의 모든 부하에게 소식을 전하는 시간
// 말단 사원은 부하가 없으므로 solve(말단) = 0이다.
int solve(int u)
{
    vector<int> cost;
    for (int v : adj[u])
        cost.push_back(solve(v));
    
    // cost에는 자기의 부하들의 solve()값이 담겨있다.

    // 말단 사원은 그냥 0
    if (cost.empty()) return 0;
    sort(cost.begin(), cost.end(), greater<int>());

    // 최적해 : 가장 시간이 오래 걸리는 애부터 전화를 돌린다.
    int ret = 0;
    for (int i = 0; i < cost.size(); ++i)
        ret = max(ret, cost[i] + i + 1);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, x; cin >> N >> x;
    for (int v = 1; v < N; ++v) {
        int u; cin >> u;
        adj[u].push_back(v);
    }
    cout << solve(0);
    return 0;
}