#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    deque<int> f;
    deque<pair<int, int>> b;
    vector<int> buf;
    int cur = -1;
    for (int x; q--;) {
        char op;
        cin >> op;
        if (op == 'B') {
            if (!b.empty()) {
                f.emplace_front(cur);
                cur = b.front().first;
                b.pop_front();
            }
        } else if (op == 'F') {
            if (!f.empty()) {
                b.emplace_front(cur, 0);
                cur = f.front();
                f.pop_front();
            }
        } else if (op == 'C') {
            while (!b.empty() && !b.front().second) {
                if (buf.empty() || buf.back() != b.front().first) {
                    buf.emplace_back(b.front().first);
                }
                b.pop_front();
            }
            while (!buf.empty()) {
                if (b.empty() || b.front().first != buf.back()) {
                    b.emplace_front(buf.back(), 1);
                }
                buf.pop_back();
            }
        } else {
            cin >> x, --x;
            if (~cur) b.emplace_front(cur, 0);
            cur = x;
            f.clear();
        }
    }
    cout << cur + 1 << '\n';
    if (b.empty()) {
        cout << "-1\n";
    } else {
        for (const auto& [x, _] : b) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
    if (f.empty()) {
        cout << "-1\n";
    } else {
        for (const auto& x : f) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}