#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    auto xor_1tok = [&](int64_t k) -> int64_t {
        if (k % 4 == 0) return k;
        if (k % 4 == 1) return 1;
        if (k % 4 == 2) return k + 1;
        return 0;
    };

    int64_t sum = 0;
    for (int64_t x, m; n--;) {
        cin >> x >> m;
        sum ^= xor_1tok(x + m - 1) ^ xor_1tok(x - 1);
    }
    cout << (sum ? "koosaga" : "cubelover");
}