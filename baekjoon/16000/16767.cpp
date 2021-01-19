#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int i, a, t;
    bool operator<(const elem& rhs) const {
        return i > rhs.i;
    }
};

elem cow[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> cow[i].a >> cow[i].t, cow[i].i = i;

    sort(cow, cow + n, [&](auto& a, auto& b) {
        return a.a < b.a;
    });
    cow[n].a = INT_MAX;

    priority_queue<elem> pq;
    int ans = 0;
    elem who;
    for (int i = 0, cur = 0;;) {
        // cow[n] is sentinel
        for (; cow[i].a <= cur; ++i)
            pq.emplace(cow[i]);

        if (pq.empty()) {
            if (i == n) break;
            who = cow[i++];
            cur = who.a;
        } else {
            who = pq.top();
            pq.pop();
        }

        ans = max(ans, cur - who.a);
        cur += who.t;
    }
    cout << ans;
}