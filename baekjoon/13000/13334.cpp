#include <bits/stdc++.h>
using namespace std;
struct line {
    int s, e;
    bool operator<(const line& rhs) const {
        return s > rhs.s;
    }
};

const int mxN = 1e5;

line a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, L;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].s >> a[i].e;
    cin >> L;

    for (int i = 0; i < N; ++i)
        if (a[i].s > a[i].e)
            swap(a[i].s, a[i].e);
    sort(a, a + N, [&](auto& a, auto& b) {
        return a.e < b.e;
    });

    priority_queue<line> pq;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        pq.emplace(a[i]);
        while (!pq.empty() && pq.top().s < a[i].e - L)
            pq.pop();
        ans = max(ans, (int)pq.size());
    }
    cout << ans;
    return 0;
}