#include <bits/stdc++.h>
using namespace std;
struct work {
    int d, e;
};

const int mxN = 2e5;

work a[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].d >> a[i].e;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.d > b.d;
    });

    priority_queue<int> pq;
    int cur = a[0].d, ans = 0;
    for (int cur = a[0].d, i = 0; cur; --cur) {
        while (a[i].d >= cur)
            pq.emplace(a[i++].e);
        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans;
    return 0;
}