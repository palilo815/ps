#include <bits/stdc++.h>
using namespace std;

const int range = 100000;

bool visited[range + 1];
deque<int> dq;

inline void go(int v, bool f) {
    if (v < 0 || v > range || visited[v]) return;
    visited[v] = true;
    f ? dq.emplace_front(v) : dq.emplace_back(v);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int src, dst; cin >> src >> dst;
    visited[src] = true;

    dq.emplace_back(src);
    dq.emplace_back(-1);

    int ans = 0;
    while (1) {
        int u = dq.front(); dq.pop_front();
        if (u == -1) {
            ++ans; dq.emplace_back(u);
            continue;
        }
        if (u == dst) break;

        go(u * 2, true);
        go(u - 1, false);
        go(u + 1, false);
    }
    cout << ans;
    return 0;
}