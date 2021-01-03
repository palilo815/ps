#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
int a[mxN], cnt1[mxN + 1], cnt2[mxN + 1];
int64_t ans;

void dfs(int u) {
    int num = a[u];
    ans += cnt2[num] - cnt1[num];
    for (int i = 1; i * i <= num; ++i)
        if (num % i == 0) {
            ans += cnt1[i], ++cnt2[i];
            if (i * i != num) ans += cnt1[num / i], ++cnt2[num / i];
        }
    ++cnt1[num];

    for (int& v : adj[u])
        dfs(v);

    --cnt1[num];
    for (int i = 1; i * i <= num; ++i)
        if (num % i == 0) {
            --cnt2[i];
            if (i * i != num) --cnt2[num / i];
        }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 1, p; i < n; ++i) {
        cin >> p;
        adj[p - 1].emplace_back(i);
    }

    dfs(0);

    cout << ans;
}