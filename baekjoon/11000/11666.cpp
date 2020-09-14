#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 3e5;

p a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> a[i].first >> a[i].second;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.first < b.first;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        while (!pq.empty() && pq.top() + M < a[i].first)
            pq.pop();
        if (!pq.empty() && pq.top() <= a[i].first) ++ans, pq.pop();
        pq.emplace(a[i].first + a[i].second);
    }
    cout << ans;
    return 0;
}