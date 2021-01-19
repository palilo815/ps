#include <bits/stdc++.h>
using namespace std;

const int mxA = 5e4;
const int mxT = 1e6;

int a[mxA], b[mxA];
pair<int, int> t[mxT];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int A, B, T;
    cin >> A >> B >> T;

    for (int i = 0; i < A; ++i)
        cin >> a[i];
    for (int i = 0; i < B; ++i)
        cin >> b[i];
    for (int i = 0; i < T; ++i)
        cin >> t[i].first >> t[i].second;

    sort(a, a + A);
    sort(b, b + B);
    sort(t, t + T, [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    for (int i = 0; i < T; ++i)
        if (t[i].first >= a[A - 1] && t[i].second >= b[B - 1])
            return cout << -1, 0;
    t[T].first = INT_MAX;

    auto valid = [&](int m) {
        priority_queue<int> pq;
        int j = 0;
        for (int i = 0; i < A; ++i) {
            // t[T] is sentinel
            for (; t[j].first < a[i]; ++j)
                pq.emplace(t[j].second);
            for (int cnt = min(int(pq.size()), m); cnt--;)
                pq.pop();
        }
        for (; j < T; ++j)
            pq.emplace(t[j].second);
        for (int i = B - 1; ~i && !pq.empty() && pq.top() < b[i]; --i)
            for (int cnt = min(int(pq.size()), m); cnt--;)
                pq.pop();
        return pq.empty();
    };

    int lo = 0, hi = T;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        valid(m) ? hi = m : lo = m + 1;
    }
    cout << lo;
}