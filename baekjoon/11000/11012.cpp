#include <bits/stdc++.h>
using namespace std;

struct node_t {
    int val, lson, rson;
    node_t() = default;
};

constexpr int MX_N = 1e4;
constexpr int MX_X = 1e5;
constexpr int SG_X = 131072;

pair<int, int> egg[MX_N | 1];
int root[MX_X + 2];
vector<node_t> node;

void update(int qi, int l, int r, int i) {
    if (r - l == 1) return;
    node.emplace_back(node[i]);
    ++node.back().val;
    const int m = (l + r) >> 1;
    if (qi < m) {
        node.emplace_back(node[node[i].lson]);
        ++node.back().val;
        node[i].lson = node.size() - 1;
        update(qi, l, m, node[i].lson);
    } else {
        node.emplace_back(node[node[i].rson]);
        ++node.back().val;
        node[i].rson = node.size() - 1;
        update(qi, m, r, node[i].rson);
    }
}

int query(int ql, int qr, int l, int r, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return node[i].val;
    const int m = (l + r) >> 1;
    return query(ql, qr, l, m, node[i].lson) + query(ql, qr, m, r, node[i].rson);
}

void solve() {
    int n, m;
    cin >> n >> m;
    node.resize(SG_X << 1);
    for (int i = 1; i < SG_X; ++i) {
        node[i] = {0, i << 1, i << 1 | 1};
    }
    fill(node.begin() + SG_X, node.end(), node_t {});
    for (int i = 0; i < n; ++i) {
        cin >> egg[i].first >> egg[i].second;
    }
    sort(egg, egg + n, [&](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    egg[n].first = -1; // sentinel
    root[0] = 1;
    for (int x = 0, ptr = 0; x <= MX_X; ++x) {
        root[x + 1] = node.size();
        node.emplace_back(node[root[x]]);
        for (; egg[ptr].first == x; ++ptr) {
            ++node[root[x + 1]].val;
            update(egg[ptr].second, 0, SG_X, root[x + 1]);
        }
    }
    int64_t ans = 0;
    for (int x1, x2, y1, y2; m--;) {
        cin >> x1 >> x2 >> y1 >> y2, ++x2, ++y2;
        ans += query(y1, y2, 0, SG_X, root[x2]) - query(y1, y2, 0, SG_X, root[x1]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}