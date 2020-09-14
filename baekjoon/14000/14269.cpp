#include <bits/stdc++.h>
using namespace std;
struct elem {
    int A, B, C;
};

const int mxN = 1e5;

elem a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].A >> a[i].B >> a[i].C;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.A < b.A;
    });

    int ans = 1;
    for (int i = 1; i < N; ++i)
        if (a[i].A != a[i - 1].A)
            ++ans;

    for (int i = 0; i < N; ++i) {
        auto lo = lower_bound(a, a + N, elem{a[i].B, 0, 0}, [&](auto & a, auto & b) {
            return a.A < b.A;
        });
        if (lo == a + i) ++lo;
        if (lo != a + N && lo->A <= a[i].C)
            a[i].B = a[i].C = INT_MAX;
    }

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.B < b.B;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; ++i) {
        if (a[i].B == INT_MAX) break;

        if (!pq.empty() && pq.top() < a[i].B) {
            ++ans;
            while (!pq.empty()) pq.pop();
        }

        pq.emplace(a[i].C);
    }
    if (!pq.empty()) ++ans;

    cout << ans;
    return 0;
}