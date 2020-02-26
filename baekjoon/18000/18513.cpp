#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<int> cache;
    queue<int> q;
    int N, K; cin >> N >> K;
    int cnt = N + K;
    while (N--) {
        int x; cin >> x;
        q.push(x);
        cache.insert(x);
    }
    int dist = 0, ans = 0;
    while (1) {
        int q_size = q.size();
        while (q_size--) {
            int u = q.front(); q.pop();
            ans += dist;
            if (--cnt == 0) {
                cout << ans; return 0;
            }
            if (cache.find(u + 1) == cache.end()) {
                cache.insert(u + 1);
                q.push(u + 1);
            }
            if (cache.find(u - 1) == cache.end()) {
                cache.insert(u - 1);
                q.push(u - 1);
            }
        }
        ++dist;
    }
    return 0;
}