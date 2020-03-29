#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

p menu[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> menu[i].first >> menu[i].second;
    sort(menu, menu + N);

    while (Q--) {
        int u, v, x, y; cin >> u >> v >> x >> y;
        auto lo = lower_bound(menu, menu + N, make_pair(u, 0));
        auto hi = upper_bound(menu, menu + N, make_pair(v + 1, 0));

        int cnt = 0;
        for (auto it = lo; it != hi; ++it)
            if (x <= it->second && it->second <= y)
                ++cnt;
        cout << cnt << '\n';
    }
    return 0;
}