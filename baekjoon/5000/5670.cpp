#include <bits/stdc++.h>
using namespace std;

class trie {
    enum {
        alpha = 26,
        offset = 'a',
    };
    struct trie_node {
        bool has_unique, has_endpoint;
        array<int, alpha> child;
        trie_node() = default;
    };

public:
    trie() : tree(1) {}

    void add(const string& s) {
        int node = 0;
        for (const auto& c : s) {
            if (tree[node].child[c - offset]) {
                tree[node].has_unique = false;
            } else {
                tree[node].child[c - offset] = tree.size();
                tree.emplace_back();
            }
            node = tree[node].child[c - offset];
        }
        tree[node].has_endpoint = true;
    }
    int query(const string& s) const {
        int node = 0, ret = 0;
        for (const auto& c : s) {
            if (tree[node].has_endpoint || !tree[node].has_unique) ++ret;
            node = tree[node].child[c - offset];
        }
        return ret;
    }
    void find_uniques() {
        for (auto& node : tree) {
            node.has_unique = count(node.child.begin(), node.child.end(), 0) == alpha - 1;
        }
        tree.front().has_unique = false;
    }

private:
    vector<trie_node> tree;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int n; cin >> n;) {
        vector<string> a(n);
        for (auto& x : a) {
            cin >> x;
        }
        trie tr;
        for (const auto& x : a) {
            tr.add(x);
        }
        tr.find_uniques();
        int64_t ans = 0;
        for (const auto& x : a) {
            ans += tr.query(x);
        }
        cout << fixed << setprecision(2) << 1.0 * ans / n << '\n';
    }
}