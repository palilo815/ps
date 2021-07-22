#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(k);
    for (auto& [x, y] : a) {
        cin >> x >> y;
        if (x > y) {
            swap(x, y);
        }
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });
    int ans = 1, done = 1;
    for (const auto& [x, y] : a) {
        if (done <= x) {
            done = y;
            ++ans;
        }
    }
    cout << ans;
}