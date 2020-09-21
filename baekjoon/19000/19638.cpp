#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, H, T;
    cin >> N >> H >> T;

    priority_queue<int> pq;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        pq.emplace(x);
    }

    int ans = 0;
    while (ans < T) {
        if (pq.top() < H || pq.top() == 1) break;
        int x = pq.top();
        pq.pop();
        pq.emplace(x >> 1);
        ++ans;
    }
    if (pq.top() < H)
        cout << "YES\n"
             << ans;
    else
        cout << "NO\n"
             << pq.top();
    return 0;
}