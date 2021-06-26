#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    struct event {
        int x, h, add;
    };

    vector<event> events(n << 1);
    for (int i = 0, l, r, h; i < n; ++i) {
        cin >> l >> r >> h;
        events[i << 1] = {l, h, 1};
        events[i << 1 | 1] = {r, h, -1};
    }

    sort(events.begin(), events.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.x == rhs.x ? lhs.add < rhs.add : lhs.x < rhs.x;
    });

    assert(events.front().add == 1);

    multiset<int, greater<int>> heights;
    heights.emplace(events.front().h);

    int64_t ans = 0;
    for (int i = 1, prv_x = events.front().x; i < n << 1; ++i) {
        if (events[i].add == 1) {
            if (*heights.begin() < events[i].h)
                ans += int64_t(events[i].x - exchange(prv_x, events[i].x)) * *heights.begin();
            heights.emplace(events[i].h);
        } else {
            if (*heights.begin() == events[i].h)
                ans += int64_t(events[i].x - exchange(prv_x, events[i].x)) * *heights.begin();
            heights.erase(heights.find(events[i].h));
        }
    }
    cout << ans;
}