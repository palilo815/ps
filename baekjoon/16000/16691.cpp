#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int l;
    cin >> l;

    int64_t sum_l = l, sum_r = l + 2;
    for (int x = l + 1, r = l + 2;; sum_r += ++r) {
        while (x + 1 != r && sum_l < sum_r) {
            sum_l += x;
            ++x;
            sum_r -= x;
        }
        if (sum_l == sum_r)
            return cout << l << ' ' << x << ' ' << r, 0;
    }
}