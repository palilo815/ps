#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    array<int, 3> num, str;
    for (auto& x : num) cin >> x;
    for (auto& x : str) cin >> x;

    vector<int> c((num[0] + num[1] + num[2]) >> 1);
    for (auto& x : c) cin >> x;

    sort(c.begin(), c.end());

    array<pair<int, int>, 6> ride = {{{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {2, 2}}};
    sort(ride.begin(), ride.end(), [&](auto& a, auto& b) {
        return str[a.first] + str[a.second] < str[b.first] + str[b.second];
    });

    auto ok = [&](int lim) -> bool {
        auto copied_num = num;
        for (const auto& x : c) {
            if (find_if(ride.begin(), ride.end(), [&](auto& elem) {
                    const auto& [f, s] = elem;
                    if (f == s && copied_num[f] < 2) return false;
                    if (f != s && (!copied_num[f] || !copied_num[s])) return false;
                    if (x * (str[f] + str[s]) < lim) return false;
                    return --copied_num[f], --copied_num[s], true;
                }) == ride.end())
                return false;
        }
        return true;
    };

    int lo = (str[0] + str[0]) * c.front(), hi = (str[2] + str[2]) * c.back();
    while (lo != hi) {
        int mid = (lo + hi + 1) >> 1;
        ok(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}