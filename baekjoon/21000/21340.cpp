#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    auto ask = [&](int x, int y) {
        cout << x << ' ' << y << endl;
        int64_t res;
        cin >> res;
        return res;
    };

    int n;
    cin >> n;

    while (n--) {
        auto d = ask(0, 0);
        if (d == 0) continue;

        vector<pair<int, int>> candi;

        for (int64_t x = 0; x * x <= d; ++x) {
            int64_t y2 = d - x * x;

            int64_t lo = 0, hi = 1e6;
            while (lo != hi) {
                auto mid = (lo + hi) >> 1;
                (mid * mid < y2) ? lo = mid + 1 : hi = mid;
            }

            if (lo * lo == y2)
                candi.emplace_back(x, lo);
        }

        for (const auto& [x, y] : candi)
            if (ask(x, y) == 0)
                break;
    }
}