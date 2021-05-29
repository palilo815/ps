#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;

    vector<pair<int, int>> mov(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> mov[i].first >> mov[i].second;

    unordered_set<int64_t> st;
    for (const auto& [x, y] : mov) {
        int64_t nx = bx - x, ny = by - y;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= n)
            st.emplace(nx << 32 | ny);
    }

    for (const auto& [x, y] : mov) {
        int64_t nx = ax + x, ny = ay + y;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= n && st.count(nx << 32 | ny))
            return cout << "Alice wins", 0;
    }

    st.clear();
    for (const auto& [x, y] : mov) {
        int64_t nx = bx + x, ny = by + y;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= n)
            st.emplace(nx << 32 | ny);
    }

    if (n < 1000) {
        unordered_set<int64_t> st2 = st;
        for (const auto& mask : st) {
            auto x = mask >> 32;
            auto y = mask & 0xffffffff;
            for (const auto& [dx, dy] : mov) {
                int64_t nx = x + dx, ny = y + dy;
                if (1 <= nx && nx <= n && 1 <= ny && ny <= n)
                    st2.emplace(nx << 32 | ny);
            }
        }

        for (int64_t i = 1; i <= n; ++i)
            for (int64_t j = 1; j <= n; ++j)
                if (!st2.count(i << 32 | j))
                    return cout << "tie " << i << ' ' << j, 0;
    } else {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<unsigned> distribution(0, n);

        for (int i = 1000; i--;) {
            int x = distribution(rng);
            int y = distribution(rng);
            bool capture = false;

            for (const auto& [dx, dy] : mov) {
                int64_t nx = x - dx, ny = y - dy;
                if (1 <= nx && nx <= n && 1 <= ny && ny <= n && st.count(nx << 32 | ny)) {
                    capture = true;
                    break;
                }
            }
            if (!capture) return cout << "tie " << x << ' ' << y, 0;
        }
    }
    cout << "Bob wins";
}