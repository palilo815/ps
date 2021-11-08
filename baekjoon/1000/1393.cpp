#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int tx, ty, x, y, dx, dy;
    cin >> tx >> ty >> x >> y >> dx >> dy;
    {
        const auto g = gcd(dx, dy);
        dx /= g, dy /= g;
    }
    const auto dist = [&](int x, int y) {
        return (x - tx) * (x - tx) + (y - ty) * (y - ty);
    };
    for (;; x += dx, y += dy) {
        if (dist(x, y) <= dist(x + dx, y + dy)) {
            return cout << x << ' ' << y, 0;
        }
    }
}