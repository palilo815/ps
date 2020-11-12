#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e9 + 1;

struct node {
    int cnt;
    node *left, *right;
    node() : cnt(0), left(NULL), right(NULL) {}
};

node* root = new node();

void update(int ql, int qr, int l = 1, int r = mxN, node* n = root) {
    if (qr <= l || r <= ql || n->cnt == r - l) return;
    if (ql <= l && r <= qr) {
        n->cnt = r - l;
        return;
    }

    if (!n->left) n->left = new node();
    if (!n->right) n->right = new node();

    int m = (l + r) >> 1;
    update(ql, qr, l, m, n->left), update(ql, qr, m, r, n->right);
    n->cnt = n->left->cnt + n->right->cnt;
}
int query(int ql, int qr, int l = 1, int r = mxN, node* n = root) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return n->cnt;
    if (n->cnt == r - l) return min(r, qr) - max(l, ql);

    int m = (l + r) >> 1, ret = 0;
    if (n->left) ret += query(ql, qr, l, m, n->left);
    if (n->right) ret += query(ql, qr, m, r, n->right);
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int M;
    cin >> M;

    char q;
    for (int c = 0, l, r; M--;) {
        cin >> q >> l >> r;
        l += c, r += c + 1;
        if (q == '1')
            cout << (c = query(l, r)) << '\n';
        else
            update(l, r);
    }
}