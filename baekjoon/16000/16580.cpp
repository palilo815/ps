#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> psum(n + 1), zeros(n + 1);
    for (int i = 0; i < n; ++i) {
        psum[i + 1] = psum[i] + a[i];
        zeros[i + 1] = zeros[i] + !a[i];
    }

    vector<tuple<int, int, int>> intervals(k);
    for (auto& [l, r, chance] : intervals) {
        cin >> l >> r >> chance, --l;
        int mx_val = (psum[r] - psum[l]) + (zeros[r] - zeros[l]);
        if (mx_val < chance) return cout << "Impossible", 0;
        chance = (mx_val - chance) >> 1;
    }

    sort(intervals.begin(), intervals.end(), [&](auto& a, auto& b) {
        return get<0>(a) == get<0>(b) ? get<1>(a) < get<1>(b) : get<0>(a) < get<0>(b);
    });

    struct elem {
        int d, u;
        elem(int d, int u) : d(d), u(u) {}
        bool operator<(const elem& rhs) const {
            return d > rhs.d;
        }
    };

    priority_queue<elem> pq;
    for (int i = 0, j = 0, neg = 0; i < n; ++i) {
        while (!pq.empty() && pq.top().u <= i) pq.pop();
        for (; j < k && get<0>(intervals[j]) == i; ++j)
            pq.emplace(get<2>(intervals[j]) + neg, get<1>(intervals[j]));
        if (a[i]) continue;

        if (pq.empty() || pq.top().d > neg)
            a[i] = -1, ++neg;
        else
            a[i] = 1;
    }

    for (const auto& x : a)
        cout << x << ' ';
}