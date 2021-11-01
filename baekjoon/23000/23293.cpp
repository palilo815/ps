#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int t, n;
    cin >> t >> n;
    vector<int> bad_log, bad_id;
    vector<int> loc(n + 1, 1);
    vector<array<int, 54>> has(n + 1);
    for (int i = 1, lg, id, x, y; i <= t; ++i) {
        char op;
        cin >> lg >> id >> op >> x;
        if (op == 'M') {
            if (exchange(loc[id], x) == x) {
                bad_log.emplace_back(i);
            }
        } else if (op == 'F') {
            ++has[id][x];
            if (loc[id] != x) {
                bad_log.emplace_back(i);
            }
        } else if (op == 'A') {
            if (loc[id] != loc[x]) {
                bad_log.emplace_back(i);
                bad_id.emplace_back(id);
            }
        } else {
            cin >> y;
            if (!has[id][x] || !has[id][y]) {
                bad_log.emplace_back(i);
            }
            has[id][x] = has[id][x] ? has[id][x] - 1 : 0;
            has[id][y] = has[id][y] ? has[id][y] - 1 : 0;
        }
    }
    sort(bad_id.begin(), bad_id.end());
    bad_id.erase(unique(bad_id.begin(), bad_id.end()), bad_id.end());
    cout << bad_log.size() << '\n';
    if (!bad_log.empty()) {
        for (const auto& x : bad_log) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    cout << bad_id.size() << '\n';
    if (!bad_id.empty()) {
        for (const auto& x : bad_id) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}