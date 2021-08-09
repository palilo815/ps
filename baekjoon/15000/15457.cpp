#include <bits/stdc++.h>
using namespace std;

struct pie {
    int t_you, t_me, id;
    pie(int t_you, int t_me, int id) : t_you(t_you), t_me(t_me), id(id) {}
    bool operator<(const pie& rhs) const {
        return t_you < rhs.t_you;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, d;
    cin >> n >> d;
    multiset<pie> bessie, elsie;
    vector dist(n << 1, -1);
    queue<pie> q;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        if (y) {
            bessie.emplace(y, x, i);
        } else {
            dist[i] = 1;
            q.emplace(y, x, i);
        }
    }
    for (int i = n, x, y; i < n << 1; ++i) {
        cin >> x >> y;
        if (x) {
            elsie.emplace(x, y, i);
        } else {
            dist[i] = 1;
            q.emplace(x, y, i);
        }
    }
    while (!q.empty()) {
        const auto [t_you, t_me, id] = q.front();
        q.pop();
        auto& you = id < n ? elsie : bessie;
        for (auto it = you.lower_bound(pie(t_me - d, 0, 0)); it != you.end(); it = you.erase(it)) {
            if (it->t_you > t_me) break;
            dist[it->id] = dist[id] + 1;
            q.emplace(*it);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << dist[i] << '\n';
    }
}