#include <bits/stdc++.h>
using namespace std;

struct elem {
    int dx, dv, i, j;
    elem(int dx, int dv, int i, int j) : dx(dx), dv(dv), i(i), j(j) {}
    bool operator<(const elem& rhs) const {
        return int64_t(dx) * rhs.dv > int64_t(rhs.dx) * dv;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto& [x, v] : a) cin >> x >> v;

    priority_queue<elem> pq;
    auto push_pq = [&](int i, int j) {
        int dx = a[j].first - a[i].first;
        int dv = a[i].second - a[j].second;
        if (dv > 0)
            pq.emplace(dx, dv, i, j);
    };

    for (int i = 0; i < n - 1; ++i)
        push_pq(i, i + 1);

    vector<bool> broken(n);
    vector<int> lft(n), rht(n);
    iota(lft.begin(), lft.end(), -1);
    iota(rht.begin(), rht.end(), 1);

    while (!pq.empty()) {
        const auto [_dx, _dv, i, j] = pq.top();
        pq.pop();

        if (broken[i] || broken[j]) continue;
        broken[i] = broken[j] = true;

        int l = lft[i], r = rht[j];
        if (l != -1) rht[l] = r;
        if (r != n) lft[r] = l;

        if (l != -1 && r != n)
            push_pq(l, r);
    }

    cout << count(broken.begin(), broken.end(), false) << '\n';
    for (int i = 0; i < n; ++i)
        if (!broken[i])
            cout << i + 1 << ' ';
}