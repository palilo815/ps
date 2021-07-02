#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int TC = 0;

TOP:;
    int n;
    cin >> n;
    if (!n) return 0;

    int x_min = INT_MIN, x_max = INT_MAX,
        y_min = INT_MIN, y_max = INT_MAX;

    int x0, y0;
    cin >> x0 >> y0;

    for (int x, y; --n; x0 = x, y0 = y) {
        cin >> x >> y;
        if (x == x0) {
            if (y < y0) {
                chmin(x_max, x);
            } else if (y > y0) {
                chmax(x_min, x);
            } else {
                assert(false);
            }
        } else if (y == y0) {
            if (x < x0) {
                chmax(y_min, y);
            } else if (x > x0) {
                chmin(y_max, y);
            } else {
                assert(false);
            }
        } else {
            assert(false);
        }
    }

    cout << "Floor #" << ++TC << '\n'
         << "Surveillance is " << (x_min > x_max || y_min > y_max ? "im" : "") << "possible.\n"
         << '\n';
    goto TOP;
}