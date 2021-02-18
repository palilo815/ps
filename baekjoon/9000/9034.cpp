#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> tree;
    int n;

    BIT(int n) : tree(n + 1), n(n) {
        tree[n] = n;
    }
    void add(int i) {
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    void sub(int i) {
        for (++i; i <= n; i += i & -i)
            --tree[i];
    }
    int query(int r) {
        int ret = 0;
        for (; r; r -= r & -r)
            ret += tree[r];
        return ret;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> q(m);
    int R = 0;
    for (int i = 0; i < m; ++i) {
        char op;
        cin >> op;
        if (op == 'R')
            cin >> q[i].first >> q[i].second, --q[i].first, ++R;
        else
            cin >> q[i].first, --q[i].first, q[i].second = -1;
    }

    vector<int> score(n), ord(R + 1);
    for (int i = 0, sz = 1; i < m; ++i)
        if (~q[i].second)
            ord[sz++] = score[q[i].first] += q[i].second;

    sort(ord.begin(), ord.end(), greater<int>());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    fill(score.begin(), score.end(), 0);

    BIT bit(ord.size());

#define ranking lower_bound(ord.begin(), ord.end(), score[id], greater<int>()) - ord.begin()
    for (const auto& [id, val] : q) {
        if (val == -1) cout << bit.query(ranking) + 1 << '\n';
        else {
            bit.sub(ranking);
            score[id] += val;
            bit.add(ranking);
        }
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}