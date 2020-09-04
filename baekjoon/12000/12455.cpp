#include <bits/stdc++.h>
using namespace std;
struct coffee {
    int c, t, s;
};
struct elem {
    int c, s;
    elem(int c, int s) : c(c), s(s) {}
    bool operator <(const elem& rhs) const {
        return s < rhs.s;
    }
};

const int mxN = 8;

coffee a[mxN];

int solve() {
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i].c >> a[i].t >> a[i].s;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.t > b.t;
    });

    priority_queue<elem> pq;
    pq.emplace(a[0].c, a[0].s);

    int ret = 0, cur = a[0].t;
    for (int i = 1; i < N; ++i) {
        int gap = cur - a[i].t;
        cur = a[i].t;

        while (gap && !pq.empty()) {
            auto [c, s] = pq.top(); pq.pop();
            int drink = min(c, gap);

            gap -= drink, c -= drink, ret += s * drink;
            if (c) pq.emplace(c, s);
        }
        pq.emplace(a[i].c, a[i].s);
    }

    while (cur && !pq.empty()) {
        auto [c, s] = pq.top(); pq.pop();
        int drink = min(c, cur);

        cur -= drink, c -= drink, ret += s * drink;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
    return 0;
}