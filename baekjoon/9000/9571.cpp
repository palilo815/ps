#include <bits/stdc++.h>
using namespace std;
struct cow {
    int x, h;
    bool operator<(const cow& rhs) const {
        return h < rhs.h;
    }
};

const int mxN = 5e4;

cow a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, D;
    cin >> N >> D;
    for (int i = 0; i < N; ++i)
        cin >> a[i].x >> a[i].h;

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    vector<bool> crowded(N, true);
    priority_queue<cow> pq;

    for (int i = 0; i < N; ++i) {
        pq.emplace(a[i]);
        while (pq.top().x < a[i].x - D) pq.pop();
        if (pq.top().h < a[i].h * 2) crowded[i] = false;
    }

    while (!pq.empty()) pq.pop();

    for (int i = N - 1; ~i; --i) {
        pq.emplace(a[i]);
        while (pq.top().x > a[i].x + D) pq.pop();
        if (pq.top().h < a[i].h * 2) crowded[i] = false;
    }

    cout << count(crowded.begin(), crowded.end(), true);
    return 0;
}