#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    struct info_t {
        int id, x, y, z;
    };
    int n;
    cin >> n;
    vector<info_t> a(n);
    for (auto& [id, x, y, z] : a) {
        cin >> id >> x >> y >> z;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        auto l = lhs.x * lhs.y * lhs.z;
        auto r = rhs.x * rhs.y * rhs.z;
        if (l != r) return l < r;
        l = lhs.x + lhs.y + lhs.z;
        r = rhs.x + rhs.y + rhs.z;
        if (l != r) return l < r;
        return lhs.id < rhs.id;
    });
    cout << a[0].id << ' ' << a[1].id << ' ' << a[2].id;
}