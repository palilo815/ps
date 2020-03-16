#include <bits/stdc++.h>
using namespace std;

const int max_N = 900;

int K, N;
int cnt[max_N + 1];
vector<int> adj[max_N + 1];
vector<int> ans;

bool solve(int idx, int k) {
    if (k == 0) return true;
    for (int i = idx + 1; i <= N; ++i) if (adj[i].size() >= K - 1) {
        bool inssa = true;
        for(int j : ans)
            if (!binary_search(adj[i].begin(), adj[i].end(), j)) {
                inssa = false;
                break;
            }
        if (!inssa) continue;
        ans.emplace_back(i);
        if (solve(i, k - 1)) return true;
        ans.pop_back();
    }
    return false;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int F; cin >> K >> N >> F;
    while (F--) {
        int u, v; cin >> u >> v;
        ++cnt[u], ++cnt[v];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    // x의 친구가 K - 1명 이상이면,
    // x가 ans vector의 모든 학생과 친구관계인지 확인한다.
    // 맞다면 ans에 넣는다.
    // ans에 K개의 학생을 넣었다면 답을 찾은 것이고 아니라면 -1

    for (int i = 1; i <= N; ++i) if (adj[i].size() >= K - 1)
        sort(adj[i].begin(), adj[i].end());

    if (solve(0, K)) for (int i : ans) cout << i << '\n';
    else cout << -1;
    return 0;
}