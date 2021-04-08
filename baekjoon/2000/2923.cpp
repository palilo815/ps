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

    array<int, 100> cntA {}, cntB {};
    auto get_min = [&]() {
        int ret = INT_MIN;
        for (int pa = -1, pb = 100, ca = 0, cb = 0;;) {
            if (!ca) {
                for (++pa; pa < 100 && !cntA[pa]; ++pa)
                    ;
                if (pa == 100) break;
                ca = cntA[pa];
            }
            if (!cb) {
                for (--pb; ~pb && !cntB[pb]; --pb)
                    ;
                cb = cntB[pb];
            }

            ret = max(ret, pa + pb);
            auto c = min(ca, cb);
            ca -= c, cb -= c;
        }
        return ret + 2;
    };

    for (int i = n, a, b; i--;) {
        cin >> a >> b;
        ++cntA[a - 1], ++cntB[b - 1];
        cout << get_min() << '\n';
    }
}