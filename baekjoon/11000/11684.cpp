#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t x, y;
    cin >> x >> y;

    int ans = 0;
    for (int A = 1; A < 64; ++A) {
        const int64_t num0 = (1LL << A) - 1;
        const int len0 = A;

        if (x <= num0 && num0 <= y)
            ++ans;
        else if (y < num0)
            continue;

        for (int B = 1; A + B < 64; ++B) {
            auto num = num0;
            auto len = len0;
            for (;;) {
                if ((len += B) >= 64) break;
                num <<= B;

                if (x <= num && num <= y)
                    ++ans;
                else if (y < num)
                    break;

                if ((len += A) >= 64) break;
                num = num << A | ((1 << A) - 1);

                if (x <= num && num <= y)
                    ++ans;
                else if (y < num)
                    break;
            }
        }
    }
    cout << ans;
}