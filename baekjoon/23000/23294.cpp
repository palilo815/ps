#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q, c;
    cin >> n >> q >> c;
    vector<int> cap(n);
    for (auto& x : cap) {
        cin >> x;
    }
    deque<int> f;
    deque<pair<int, int>> b;
    vector<int> buf;
    int cur = -1, cache = 0;
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
                cache -= cap[b.front().first];
                b.pop_front();
            }
            while (!buf.empty()) {
                if (b.empty() || b.front().first != buf.back()) {
                    b.emplace_front(buf.back(), 1);
                    cache += cap[buf.back()];
                }
                buf.pop_back();
            }
        } else {
            cin >> x, --x;
            if (~cur) b.emplace_front(cur, 0);
            cur = x;
            cache += cap[x];
            for (const auto& id : f) {
                cache -= cap[id];
            }
            f.clear();
            while (cache > c) {
                cache -= cap[b.back().first];
                b.pop_back();
            }
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