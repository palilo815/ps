#include <bits/stdc++.h>
using namespace std;

constexpr int mxP = 3e6;

int grundy[mxP + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    vector<int> fibo = {1, 2};
    for (;;) {
        auto x = fibo.end()[-1] + fibo.end()[-2];
        if (x > mxP) break;
        fibo.emplace_back(x);
    }

    for (int i = 1; i <= mxP; ++i) {
        int mask = 0;
        for (const auto& f : fibo) {
            int x = i - f;
            if (x < 0) break;
            mask |= 1 << grundy[x];
        }

        for (int j = 0;; ++j)
            if (!(mask >> j & 1)) {
                grundy[i] = j;
                break;
            }
    }

    int n;
    cin >> n;

    int xorsum = 0;
    for (int x; n--;) {
        cin >> x;
        xorsum ^= grundy[x];
    }
    cout << (xorsum ? "koosaga" : "cubelover");
}