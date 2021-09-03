#include <bits/stdc++.h>
using namespace std;

struct node_t {
    int sum, lson, rson;
    node_t() = default;
};

vector<node_t> node;

constexpr int MX_B = 19;
constexpr int SG_X = 1 << MX_B;

void update(int qi, int l, int r, int i) {
    if (r - l == 1) return;
    const int m = (l + r) >> 1;
    if (qi < m) {
        node.emplace_back(node[node[i].lson]);
        ++node.back().sum;
        node[i].lson = node.size() - 1;
        update(qi, l, m, node[i].lson);
    } else {
        node.emplace_back(node[node[i].rson]);
        ++node.back().sum;
        node[i].rson = node.size() - 1;
        update(qi, m, r, node[i].rson);
    }
}

int xor_query(int x, int l, int r) {
    int ret = 0;
    for (int b = MX_B; b--;) {
        if (x >> b & 1) {
            if (node[node[r].lson].sum - node[node[l].lson].sum) {
                l = node[l].lson, r = node[r].lson;
            } else {
                l = node[l].rson, r = node[r].rson;
                ret |= 1 << b;
            }
        } else {
            if (node[node[r].rson].sum - node[node[l].rson].sum) {
                l = node[l].rson, r = node[r].rson;
                ret |= 1 << b;
            } else {
                l = node[l].lson, r = node[r].lson;
            }
        }
    }
    return ret;
}

int sum_query(int upper, int i, int l = 0, int r = SG_X) {
    if (upper <= l) return 0;
    if (r <= upper) return node[i].sum;
    const auto m = (l + r) >> 1;
    return sum_query(upper, node[i].lson, l, m) + sum_query(upper, node[i].rson, m, r);
}

int kth_query(int k, int l, int r) {
    int ret = 0;
    for (int b = 1 << (MX_B - 1); b; b >>= 1) {
        if (const auto lsum = node[node[r].lson].sum - node[node[l].lson].sum;
            k < lsum) {
            l = node[l].lson, r = node[r].lson;
        } else {
            l = node[l].rson, r = node[r].rson;
            ret |= b;
            k -= lsum;
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int m;
    cin >> m;
    node.reserve(SG_X * 2 + (MX_B + 1) * m);
    node.resize(SG_X << 1);
    for (int i = 1; i < SG_X; ++i) {
        node[i].lson = i << 1, node[i].rson = i << 1 | 1;
    }
    vector<int> root;
    root.reserve(m);
    root.emplace_back(1);
    char op;
    for (int l, r, x; m--;) {
        cin >> op;
        if (op == '1') {
            cin >> x;
            node.emplace_back(node[root.back()]);
            root.emplace_back(node.size() - 1);
            update(x, 0, SG_X, root.back());
        } else if (op == '2') {
            cin >> l >> r >> x, --l;
            cout << xor_query(x, root[l], root[r]) << '\n';
        } else if (op == '3') {
            cin >> x;
            node.resize(root.end()[-x]);
            root.erase(root.end() - x, root.end());
        } else if (op == '4') {
            cin >> l >> r >> x, --l, ++x;
            cout << sum_query(x, root[r]) - sum_query(x, root[l]) << '\n';
        } else {
            cin >> l >> r >> x, --l, --x;
            cout << kth_query(x, root[l], root[r]) << '\n';
        }
    }
}